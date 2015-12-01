#include <amp.h>
using namespace concurrency;


void parallel_for_each_simple_sgemm_tn(array_view<float, 2> c, array_view<const float, 2> a, array_view<const float, 2> b, int M, int N, int K, float alpha, float beta);
void parallel_for_each_simple_sgemm_tn_2x2(array_view<float, 2> c, array_view<const float, 2> a, array_view<const float, 2> b, int M, int N, int K, float alpha, float beta);