#pragma warning (disable : 4996)
#include <string>
#include <iostream>
#include <chrono>
#include <amp.h>
#include "dummy_sgemm.h"
#include "init_random.h"
#include "cppAMP_sgemm.h"
#include "error_checking.h"


int main(int argc, char** argv)
{
    //row major SGEMM TN
    std::cout << "C++ AMP row major SGEMM TN test." << std::endl;
    int Mvalue = atoi(argv[1]);
    int Nvalue = atoi(argv[2]);
    int Kvalue = atoi(argv[3]);
    int performance_level = atoi(argv[4]);

    float alpha = 1.3f;
    float beta = 0.7f;

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

    init_random_matrix_rowMajor(a, offA, M, K, lda);
    init_random_matrix_rowMajor(b, offB, K, N, ldb);
    init_random_matrix_rowMajor(c, offC, M, N, ldc);
    memcpy(cpuC, c, sizeof(float)*(ldc * N + offC));

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

    concurrency::array<float, 2> gpuA(lda, K);//(lda, K, a + offA);
    concurrency::array<float, 2> gpuB(ldb, N);//(ldb, N, b + offB);
    concurrency::array<float, 2> gpuC(ldc, N);//(ldc, N, c + offC);
    
    //copy the data to gpu
    concurrency::copy(a + offA, gpuA);
    concurrency::copy(b + offB, gpuB);
    concurrency::copy(c + offC, gpuC);
    


    if (performance_level == 0)
    {
        //parallel_for_each_simple_sgemm_tn(gpuC, gpuA, gpuB, M, N, K, alpha, beta);
        concurrency::parallel_for_each(
            gpuC.extent,
            [=, &gpuA, &gpuB, &gpuC](concurrency::index<2> idx) restrict(amp)
        {
            int idx0 = idx[0];
            int idx1 = idx[1];

            //gpuC[idx0][idx1] *= beta;
            float localSum = beta * gpuC[idx0][idx1];
            for (int k = 0; k < K; k++)
            {
                localSum += alpha * gpuA[k][idx0] * gpuB[k][idx1];
            }
            //localSum += alpha * gpuA[0][idx0] * gpuB[0][idx1];
            //localSum += alpha * gpuA[1][idx0] * gpuB[1][idx1];
            //localSum += alpha * gpuA[2][idx0] * gpuB[2][idx1];
            //localSum += alpha * gpuA[3][idx0] * gpuB[3][idx1];

            gpuC[idx0][idx1] = localSum;
        }
        );

        concurrency::copy(gpuC, c + offC);
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
        parallel_for_each_simple_sgemm_tn(gpuC, gpuA, gpuB, M, N, K, alpha, beta);


    }
}