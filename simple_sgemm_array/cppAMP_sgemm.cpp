#include "cppAMP_sgemm.h"
#include <amp.h>

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


void parallel_for_each_simple_sgemm_tn(array<float, 2> c, array<float, 2> a, array<float, 2> b, int M, int N, int K, float alpha, float beta) 
{
    /*
    concurrency::parallel_for_each(
        c.extent,
        [=](concurrency::index<2> idx) restrict(amp)
    {
        simple_sgemm_tn(idx, c, a, b, M, N, K, alpha, beta);
    }
    );
    c.synchronize();
    */
    concurrency::parallel_for_each(
        c.extent,
        [=,&a,&b,&c](concurrency::index<2> idx) restrict(amp)
    {
        int idx0 = idx[0];
        int idx1 = idx[1];

        c[idx0][idx1] *= beta;
        for (int k = 0; k < K; k++)
        {
            c[idx0][idx1] += alpha * a[k][idx0] * b[k][idx1];
        }
    }
    );
}