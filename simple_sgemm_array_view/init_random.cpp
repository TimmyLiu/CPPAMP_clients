#pragma once
#include "init_random.h"

template<typename T>
int init_random_matrix_rowMajor(T *Matrix, int offset, int rowSize, int columnSize, int leadingDimSize)
{
    if (rowSize == 0 || columnSize == 0)
        return -1;
    if (leadingDimSize < columnSize)
        return -2;

    //default type does not handle complex data
    for (int rowidx = 0; rowidx < rowSize; rowidx++)
    {
        for (int colidx = 0; colidx < columnSize; colidx++)
        {
        float randNumRange = static_cast<T> (rand());
        float randNum = static_cast<T>(rand() / static_cast<T>(RAND_MAX) * randNumRange);
        Matrix[rowidx*leadingDimSize + colidx + offset] = randNum;
        //Matrix[rowidx*leadingDimSize + colidx + offset] = 1;
        }
    }

}

template int init_random_matrix_rowMajor<float>(float *Matrix, int offset, int rowSize, int columnSize, int leadingDimSize);