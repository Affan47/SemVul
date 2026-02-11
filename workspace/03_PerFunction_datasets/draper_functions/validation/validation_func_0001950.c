IReadBlock( int nBlockXOff, int nBlockYOff,
                                      void * pImage )

{
    LANDataset *poLAN_DS = (LANDataset *) poDS;
    CPLAssert( nBlockXOff == 0  );


    int nOffset;

    nOffset =
        ERD_HEADER_SIZE
        + (nBlockYOff * nRasterXSize * poLAN_DS->GetRasterCount()) / 2
        + ((nBand - 1) * nRasterXSize) / 2;

    if( VSIFSeekL( poLAN_DS->fpImage, nOffset, SEEK_SET ) != 0 )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "LAN Seek failed:%s", VSIStrerror( errno ) );
        return CE_Failure;
    }


    if( VSIFReadL( pImage, 1, nRasterXSize/2, poLAN_DS->fpImage ) !=
        (size_t) nRasterXSize / 2 )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "LAN Read failed:%s", VSIStrerror( errno ) );
        return CE_Failure;
    }


    int i;

    for( i = nRasterXSize-1; i >= 0; i-- )
    {
        if( (i & 0x01) != 0 )
            ((GByte *) pImage)[i] = ((GByte *) pImage)[i/2] & 0x0f;
        else
            ((GByte *) pImage)[i] = (((GByte *) pImage)[i/2] & 0xf0)/16;
    }

    return CE_None;
}
