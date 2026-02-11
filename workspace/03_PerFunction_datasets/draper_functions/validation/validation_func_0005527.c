GDALDatasetGetBestOverviewLevel(GDALDataset* poDS,
                                    int &nXOff, int &nYOff,
                                    int &nXSize, int &nYSize,
                                    int nBufXSize, int nBufYSize,
                                    int nBandCount, int *panBandMap)
{
    int iBand, iOverview;
    int nOverviewCount = 0;
    GDALRasterBand *poFirstBand = NULL;

    if (nBandCount == 0)
        return -1;


    for( iBand = 0; iBand < nBandCount; iBand++ )
    {
        GDALRasterBand *poBand = poDS->GetRasterBand( panBandMap[iBand] );
        if (iBand == 0)
        {
            poFirstBand = poBand;
            nOverviewCount = poBand->GetOverviewCount();
        }
        else if (nOverviewCount != poBand->GetOverviewCount())
        {
            CPLDebug( "GDAL",
                      "GDALDataset::GetBestOverviewLevel() ... "
                      "mismatched overview count, use std method." );
            return -1;
        }
        else
        {
            for(iOverview = 0; iOverview < nOverviewCount; iOverview++)
            {
                GDALRasterBand* poOvrBand =
                    poBand->GetOverview(iOverview);
                GDALRasterBand* poOvrFirstBand =
                    poFirstBand->GetOverview(iOverview);
                if ( poOvrBand == NULL || poOvrFirstBand == NULL)
                    continue;

                if ( poOvrFirstBand->GetXSize() != poOvrBand->GetXSize() ||
                     poOvrFirstBand->GetYSize() != poOvrBand->GetYSize() )
                {
                    CPLDebug( "GDAL",
                              "GDALDataset::GetBestOverviewLevel() ... "
                              "mismatched overview sizes, use std method." );
                    return -1;
                }
                int nBlockXSizeFirst=0, nBlockYSizeFirst=0;
                int nBlockXSizeCurrent=0, nBlockYSizeCurrent=0;
                poOvrFirstBand->GetBlockSize(&nBlockXSizeFirst, &nBlockYSizeFirst);
                poOvrBand->GetBlockSize(&nBlockXSizeCurrent, &nBlockYSizeCurrent);
                if (nBlockXSizeFirst != nBlockXSizeCurrent ||
                    nBlockYSizeFirst != nBlockYSizeCurrent)
                {
                    CPLDebug( "GDAL",
                          "GDALDataset::GetBestOverviewLevel() ... "
                          "mismatched block sizes, use std method." );
                    return -1;
                }
            }
        }
    }

    return GDALBandGetBestOverviewLevel(poFirstBand,
                                        nXOff, nYOff, nXSize, nYSize,
                                        nBufXSize, nBufYSize);
}
