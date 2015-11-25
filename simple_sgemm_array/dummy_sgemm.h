#pragma once
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef enum dummy_sgemm_order_
{
    dummy_sgemm_column_major,
    dummy_sgemm_row_major
} dummy_sgemm_order;

typedef enum dummy_sgemm_transpose_
{
    dummy_sgemm_trans,
    dummy_sgemm_notrans,
    dummy_sgemm_conjtrans
} dummy_sgemm_transpose;

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
    size_t ldc);
#ifdef __cplusplus
}
#endif