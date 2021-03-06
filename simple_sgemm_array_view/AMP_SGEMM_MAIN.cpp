#pragma warning (disable : 4996)
#include <string>
#include <iostream>
#include <amp.h>
#include <chrono>
#include <dlfcn.h>
#include "dummy_sgemm.h"
#include "init_random.h"
#include "cppAMP_sgemm.h"
#include "error_checking.h"

int exec(const char* cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        printf("having trouble with pipe.\n");
        return 1;
    }
    char buffer[128];
    
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
        {}
    }
    return 0;
}

int main(int argc, char** argv)
{
    //row major SGEMM TN
    std::cout << "C++ AMP row major SGEMM TN test." << std::endl;
    int Mvalue = atoi(argv[1]);
    int Nvalue = atoi(argv[2]);
    int Kvalue = atoi(argv[3]);
    int performance_level = atoi(argv[4]);

    float alpha = 1.0f;
    float beta = 0.0f;

    std::cout << "M= " << Mvalue << " N= " << Nvalue << " K= " << Kvalue << " " << std::endl;
    if (performance_level == 0)
    {
        std::cout << "check result " << std::endl;
    }
    else if (performance_level == 1)
    {
        std::cout << "measure performance " << std::endl;
    }

    int M = Mvalue;
    int N = Nvalue;
    int K = Kvalue;
    size_t lda, ldb, ldc;

    //for row major SGEMM TN we know
    lda = M; //lda >= M
    ldb = N; //ldb >= N
    ldc = N; //ldc >= N
    
    size_t offA = 0;
    size_t offB = 0;
    size_t offC = 0;

    //init random matrx
    float *a, *b, *c, *cpuC;
    a = (float*)malloc((lda * K + offA) * sizeof(float));
    b = (float*)malloc((ldb * K + offB) * sizeof(float));
    c = (float*)malloc((ldc * M + offC) * sizeof(float));
    cpuC = (float*)malloc((ldc * M + offC) * sizeof(float));

    init_random_matrix_rowMajor(a, offA, K, M, lda);
    init_random_matrix_rowMajor(b, offB, K, N, ldb);
    init_random_matrix_rowMajor(c, offC, M, N, ldc);
    memcpy(cpuC, c, sizeof(float)*(ldc * M + offC));

    if (performance_level == 0)
    {
        //perform dummy gemm
        int err = dummy_sgemm(dummy_sgemm_row_major, 
                              dummy_sgemm_trans,
                              dummy_sgemm_notrans,
                              M, N, K, alpha, a, offA, lda, b, offB, ldb, beta, cpuC, offC, ldc);
        if (err < 0)
        {
            std::cout << "dummy sgemm err = " << err << std::endl;
            exit(1);
        }
    }

    concurrency::array_view<const float, 2> gpuA(K, lda, a + offA);//(lda, K, a + offA);
    concurrency::array_view<const float, 2> gpuB(K, ldb, b + offB);//(ldb, N, b + offB);
    concurrency::array_view<float, 2> gpuC(M, ldc, c + offC);//(ldc, N, c + offC);
    
    //copy the data to gpu
    //concurrency::copy(a + offA, gpuA);
    //concurrency::copy(b + offB, gpuB);
    //concurrency::copy(c + offC, gpuC);
    


    if (performance_level == 0)
    {
        int pipestaus = exec("./build_kernel_online.sh");
        void *handle;
        char *error;
        void (*parallel_for_each_simple_sgemm_tn_FT)(Concurrency::array_view<float, 2> c, Concurrency::array_view<const float, 2> a, Concurrency::array_view<const float, 2> b, int M, int N, int K, float alpha, float beta);
        handle = dlopen ("/home/timmy/Documents/Github/CPPAMP_clients/OnlineCPPAMP/simple_sgemm_array_view/libsimple_sgemm.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }
        *(void**)(&parallel_for_each_simple_sgemm_tn_FT) = dlsym(handle, "parallel_for_each_simple_sgemm_tn");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        printf("about to call simple sgemm\n");
        //parallel_for_each_simple_sgemm_tn(gpuC, gpuA, gpuB, M, N, K, alpha, beta);
        (void)parallel_for_each_simple_sgemm_tn_FT(gpuC, gpuA, gpuB, M, N, K, alpha, beta);
        printf("called simple sgemm\n");
        dlclose(handle);
        //parallel_for_each_simple_sgemm_tn_2x2(gpuC, gpuA, gpuB, M, N, K, alpha, beta);
        //concurrency::copy(gpuC, c + offC);
        bool pass = error_checking_rowMajor(cpuC, gpuC, M, N, ldc);

        if (pass == true)
        {
            std::cout << "correctness test passed. " << std::endl;
        }
        else
        {
            std::cout << "correctness test failed. " << std::endl;
        }
    }

    if (performance_level == 1)
    {
        //warm up
        //parallel_for_each_simple_sgemm_tn(gpuC, gpuA, gpuB, M, N, K, alpha, beta);
        std::cout << "the current system clock has a resolution of " << ((double)std::chrono::high_resolution_clock::period::num / (double)std::chrono::high_resolution_clock::period::den) << " seconds." << std::endl;
        int iterations = 100;

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            //parallel_for_each_simple_sgemm_tn(gpuC, gpuA, gpuB, M, N, K, alpha, beta);
            //parallel_for_each_simple_sgemm_tn_2x2(gpuC, gpuA, gpuB, M, N, K, alpha, beta);
        }

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        auto diff = end - start;
        long long flops = ((long long)2 * (long long)M * (long long)N * (long long)K * (long long)iterations) / diff.count();
        std::cout << "time: " << diff.count() << " nanoseconds." << std::endl;
        std::cout << "performance: " << flops << " GFLOPS" << std::endl;

    }
}
