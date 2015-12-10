#include "error_checking.h"
#include <iostream>
#include <math.h>

bool error_checking_rowMajor(float *mat1, concurrency::array_view<float, 2> mat2, int rowSize, int colSize, int leadingDimSize)
{
    if (rowSize == 0 && colSize == 0)
        return true;

    float *errorMat = (float*)malloc(rowSize * colSize * sizeof(float));
    for (int rowidx = 0; rowidx < rowSize; rowidx++)
    {
        for (int colidx = 0; colidx < colSize; colidx++)
        {
            float error = abs(mat1[colidx*leadingDimSize + rowidx] - mat2[colidx][rowidx]);
            //std::cout << error << " " << std::endl;
            errorMat[colidx*rowSize + rowidx] = error;
        }
    }
    
    float accuNorm = 0.0f;
    float baseNorm = 0.0f;
    for (int rowidx = 0; rowidx < rowSize; rowidx++)
    {
        for (int colidx = 0; colidx < colSize; colidx++)
        {
            accuNorm += errorMat[colidx*rowSize + rowidx] * errorMat[colidx*rowSize + rowidx];
            baseNorm += mat1[colidx*rowSize + rowidx] * mat1[colidx*rowSize + rowidx];
        }
    }

    accuNorm = sqrt(accuNorm);
    float twoNorm = accuNorm / baseNorm;

    if (twoNorm < 1e-10)
        return true;
    return false;

}
