operator* (Real fScalar, const Matrix3& rkMatrix)
    {
        Matrix3 kProd;
        for (size_t iRow = 0; iRow < 3; iRow++)
        {
            for (size_t iCol = 0; iCol < 3; iCol++)
                kProd[iRow][iCol] = fScalar*rkMatrix.m[iRow][iCol];
        }
        return kProd;
    }
