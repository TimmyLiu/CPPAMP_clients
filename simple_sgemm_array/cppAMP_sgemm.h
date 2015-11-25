#include <amp.h>
using namespace concurrency;


void parallel_for_each_simple_sgemm_tn(array<float, 2> c, array<float, 2> a, array<float, 2> b, int M, int N, int K, float alpha, float beta);