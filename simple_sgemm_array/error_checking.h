#pragma once
#include <amp.h>

bool error_checking_rowMajor(float *mat1, concurrency::array_view<float, 2> mat2, int rowSize, int colSize, int leadingDimSize);