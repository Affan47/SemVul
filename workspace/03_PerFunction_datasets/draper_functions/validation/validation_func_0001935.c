IReadBlock( int nBlockXOff, int nBlockYOff,
                                 void * pImage )

{
    long    nOffset;
    int     nTilesPerRow;
    int     nWordSize, nBlockSize;

    nTilesPerRow = (nRasterXSize + nBlockXSize - 1) / nBlockXSize;
    nWordSize = GDALGetDataTypeSize( eDataType ) / 8;
    nBlockSize = nWordSize * nBlockXSize * nBlockYSize;

    nOffset = nBlockSize * (nBlockXOff + nBlockYOff*nTilesPerRow);

    if( VSIFSeekL( fpRaw, nOffset, SEEK_SET ) == -1
        || VSIFReadL( pImage, 1, nBlockSize, fpRaw ) < 1 )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Read of tile %d/%d failed with fseek or fread error.",
                  nBlockXOff, nBlockYOff );
        return CE_Failure;
    }

    if( !bNative && nWordSize > 1 )
    {
        if( GDALDataTypeIsComplex( eDataType ) )
        {
            GDALSwapWords( pImage, nWordSize/2, nBlockXSize*nBlockYSize,
                           nWordSize );
            GDALSwapWords( ((GByte *) pImage)+nWordSize/2,
                           nWordSize/2, nBlockXSize*nBlockYSize, nWordSize );
        }
        else
            GDALSwapWords( pImage, nWordSize,
                           nBlockXSize * nBlockYSize, nWordSize );
    }

    return CE_None;
}
