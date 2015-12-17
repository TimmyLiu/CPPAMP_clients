#include <amp.h>
//using namespace concurrency;


extern "C" void parallel_for_each_simple_sgemm_tn(Concurrency::array_view<float, 2> c, Concurrency::array_view<const float, 2> a, Concurrency::array_view<const float, 2> b, int M, int N, int K, float alpha, float beta);
extern "C" void parallel_for_each_simple_sgemm_tn_2x2(Concurrency::array_view<float, 2> c, Concurrency::array_view<const float, 2> a, Concurrency::array_view<const float, 2> b, int M, int N, int K, float alpha, float beta);
extern "C" void test();