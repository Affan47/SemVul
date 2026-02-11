IReadBlock( int nBlockXOff, int nBlockYOff,
                                       void* pImage )

{
    CPLAssert( sizeof(float) == sizeof(GInt32) );
    CPLAssert( nBlockXOff == 0  );
    CPLAssert( pImage != NULL );

    LevellerDataset *poGDS = (LevellerDataset *) poDS;


    const size_t rowbytes = nBlockXSize * sizeof(float);

    if(0 != VSIFSeekL(
           poGDS->m_fp,
           poGDS->m_nDataOffset + nBlockYOff * rowbytes,
           SEEK_SET))
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  ".bt Seek failed:%s", VSIStrerror( errno ) );
        return CE_Failure;
    }


    if( VSIFReadL( pImage, rowbytes, 1, poGDS->m_fp ) != 1 )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Leveller read failed:%s", VSIStrerror( errno ) );
        return CE_Failure;
    }


#ifdef CPL_MSB
    GDALSwapWords( pImage, 4, nRasterXSize, 4 );
#endif


    float* pf = (float*)pImage;

    if(poGDS->m_version < 6)
    {
        GInt32* pi = (int*)pImage;
        for(size_t i = 0; i < (size_t)nBlockXSize; i++)
            pf[i] = (float)pi[i] / 65536;
    }


#if 0


    for(size_t i = 0; i < nBlockXSize; i++)
        pf[i] *= poGDS->m_dWorldscale;
#endif

    return CE_None;
}
