spNorm( spMatrix eMatrix )
{
MatrixPtr  Matrix = (MatrixPtr)eMatrix;
register ElementPtr pElement;
register int I;
RealNumber Max = 0.0, AbsRowSum;


    ASSERT_IS_SPARSE( Matrix );
    ASSERT_NO_ERRORS( Matrix );
    ASSERT_IS_NOT_FACTORED( Matrix );
    if (NOT Matrix->RowsLinked) spcLinkRows( Matrix );


#if REAL
    if (NOT Matrix->Complex)
    {   for (I = Matrix->Size; I > 0; I--)
        {   pElement = Matrix->FirstInRow[I];
            AbsRowSum = 0.0;
            while (pElement != NULL)
            {   AbsRowSum += ABS( pElement->Real );
                pElement = pElement->NextInRow;
            }
            if (Max < AbsRowSum) Max = AbsRowSum;
        }
    }
#endif
#if spCOMPLEX
    if (Matrix->Complex)
    {   for (I = Matrix->Size; I > 0; I--)
        {   pElement = Matrix->FirstInRow[I];
            AbsRowSum = 0.0;
            while (pElement != NULL)
            {   AbsRowSum += CMPLX_1_NORM( *pElement );
                pElement = pElement->NextInRow;
            }
            if (Max < AbsRowSum) Max = AbsRowSum;
        }
    }
#endif
    return Max;
}
