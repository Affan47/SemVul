GWKCubicNoMasksByteThread( void* pData )

{
    GWKJobStruct* psJob = (GWKJobStruct*) pData;
    GDALWarpKernel *poWK = psJob->poWK;
    int iYMin = psJob->iYMin;
    int iYMax = psJob->iYMax;

    int iDstY;
    int nDstXSize = poWK->nDstXSize;
    int nSrcXSize = poWK->nSrcXSize, nSrcYSize = poWK->nSrcYSize;


    double *padfX, *padfY, *padfZ;
    int    *pabSuccess;

    padfX = (double *) CPLMalloc(sizeof(double) * nDstXSize);
    padfY = (double *) CPLMalloc(sizeof(double) * nDstXSize);
    padfZ = (double *) CPLMalloc(sizeof(double) * nDstXSize);
    pabSuccess = (int *) CPLMalloc(sizeof(int) * nDstXSize);


    for( iDstY = iYMin; iDstY < iYMax; iDstY++ )
    {
        int iDstX;


        for( iDstX = 0; iDstX < nDstXSize; iDstX++ )
        {
            padfX[iDstX] = iDstX + 0.5 + poWK->nDstXOff;
            padfY[iDstX] = iDstY + 0.5 + poWK->nDstYOff;
            padfZ[iDstX] = 0.0;
        }


        poWK->pfnTransformer( psJob->pTransformerArg, TRUE, nDstXSize,
                              padfX, padfY, padfZ, pabSuccess );


        for( iDstX = 0; iDstX < nDstXSize; iDstX++ )
        {
            COMPUTE_iSrcOffset(pabSuccess, iDstX, padfX, padfY, poWK, nSrcXSize, nSrcYSize);


            int iBand;
            int iDstOffset;

            iDstOffset = iDstX + iDstY * nDstXSize;

            for( iBand = 0; iBand < poWK->nBands; iBand++ )
            {
                GWKCubicResampleNoMasksByte( poWK, iBand,
                                             padfX[iDstX]-poWK->nSrcXOff,
                                             padfY[iDstX]-poWK->nSrcYOff,
                                             &poWK->papabyDstImage[iBand][iDstOffset] );
            }
        }


        if (psJob->pfnProgress(psJob))
            break;
    }


    CPLFree( padfX );
    CPLFree( padfY );
    CPLFree( padfZ );
    CPLFree( pabSuccess );
}
