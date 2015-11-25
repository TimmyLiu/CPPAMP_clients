#pragma once
#ifndef __INIT_RANDOM__
#define __INIT_RANDOM__
#include <cstdlib>

//template<typename T>
//int init_random_matrix_columnMajor(T *Matrix, int offset, int rowSize, int columnSize, int leadingDimSize);
/*
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
            Matrix[colidx*leadingDimSize + rowidx + offset] = randNum;
        }
    }

}
*/
template<typename T>
int init_random_matrix_rowMajor(T *Matrix, int offset, int rowSize, int columnSize, int leadingDimSize);
/*
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
            //Matrix[rowidx*leadingDimSize + colidx + offset] = rowidx;
        }
    }

}
*/

#endif