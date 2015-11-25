#include "dummy_sgemm.h"

int dummy_sgemm(
    dummy_sgemm_order order,
    dummy_sgemm_transpose transA,
    dummy_sgemm_transpose transB,
    size_t M,
    size_t N,
    size_t K,
    float alpha,
    float *A,
    size_t offA,
    size_t lda,
    float *B,
    size_t offB,
    size_t ldb,
    float beta,
    float *C,
    size_t offC,
    size_t ldc)
{
    //only row major TN is implemented. 
    if (order == dummy_sgemm_column_major)
        return -1;
    if (transA != dummy_sgemm_trans)
        return -1;
    if (transB != dummy_sgemm_notrans)
        return -1;

    for (int CRowIdx = 0; CRowIdx < M; CRowIdx++)
    {
        for (int CColIdx = 0; CColIdx < N; CColIdx++)
        {
            C[CColIdx + CRowIdx * ldc + offC] *= beta;
            for (int i = 0; i < K; i++)
            {
                C[CColIdx + CRowIdx * ldc + offC] += A[i*lda + CRowIdx + offA] * B[i*ldb + CColIdx + offB] * alpha;
            }
        }
    }
    return 0;
}