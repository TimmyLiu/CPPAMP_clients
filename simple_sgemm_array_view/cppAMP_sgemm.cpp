#include "cppAMP_sgemm.h"
#include <amp.h>
/*
void simple_sgemm_tn(index<2> idx, array_view<float, 2> c, array_view<const float, 2> a, array_view<const float, 2> b, int M, int N, int K, float alpha, float beta) restrict(amp)
{
    // each work item works on one element of the C matrix exactly.
    // note cpp amp are row major
    int idx0 = idx[0];
    int idx1 = idx[1];

    c[idx0][idx1] *= beta;
    for (int k = 0; k < K; k++)
    {
        c[idx0][idx1] += alpha * a[k][idx0] * b[k][idx1];
    }


}
*/
void test()
{
    printf("im in test.");
}

void parallel_for_each_simple_sgemm_tn(Concurrency::array_view<float, 2> c, Concurrency::array_view<const float, 2> a, Concurrency::array_view<const float, 2> b, int M, int N, int K, float alpha, float beta)
{
    printf("I am inside simple sgemm\n");
    Concurrency::extent<2> compute_domain(M, N);
    
    Concurrency::parallel_for_each(
        compute_domain,
        [=](Concurrency::index<2> idx) restrict(amp)
    {
        //simple_sgemm_tn(idx, c, a, b, M, N, K, alpha, beta);
            int idx0 = idx[0];
            int idx1 = idx[1];

            c[idx0][idx1] *= beta;
            for (int k = 0; k < K; k++)
            {
                c[idx0][idx1] += alpha * a[k][idx0] * b[k][idx1];
            }
    }
    );
    c.synchronize();
    
    printf("M=%i, N=%i, K=%i, alpha=%f, beta=%f\n", M, N, K, alpha, beta);
}

/*
void simple_sgemm_tn_2x2(index<2> idx, array_view<float, 2> c, array_view<const float, 2> a, array_view<const float, 2> b, int M, int N, int K, float alpha, float beta) restrict(amp)
{
    // each work item works on 2x2 block of the C matrix exactly.
    // note cpp amp are row major
    int idx0 = idx[0]*2;
    int idx1 = idx[1]*2;

    c[idx0][idx1] *= beta;
    c[idx0][idx1+1] *= beta;
    c[idx0+1][idx1] *= beta;
    c[idx0+1][idx1+1] *= beta;

    for (int k = 0; k < K; k++)
    {
        c[idx0][idx1] += alpha * a[k][idx0] * b[k][idx1];
        c[idx0][idx1 + 1] += alpha * a[k][idx0] * b[k][idx1 + 1];
        c[idx0 + 1][idx1] += alpha * a[k][idx0 + 1] * b[k][idx1];
        c[idx0 + 1][idx1 + 1] += alpha * a[k][idx0 + 1] * b[k][idx1 + 1];
    }


}
*/
void parallel_for_each_simple_sgemm_tn_2x2(Concurrency::array_view<float, 2> c, Concurrency::array_view<const float, 2> a, Concurrency::array_view<const float, 2> b, int M, int N, int K, float alpha, float beta)
{
    //increase the work load per thread. 
    //each thread will compute a 2x2 block
    //the number of threads need would be 1/2*1/2 of 1 element per thread approach

    Concurrency::extent<2> compute_domain(M / 2, N / 2);

    concurrency::parallel_for_each(
        compute_domain,
        [=](concurrency::index<2> idx) restrict(amp)
    {
        //simple_sgemm_tn_2x2(idx, c, a, b, M, N, K, alpha, beta);
    }
    );
    c.synchronize();
}