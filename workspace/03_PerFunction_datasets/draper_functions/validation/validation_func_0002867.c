GDALDatasetShadow_BeginAsyncReader(GDALDatasetShadow *self,int xOff,int yOff,int xSize,int ySize,int buf_len,char *buf_string,void *pyObject,int buf_xsize,int buf_ysize,GDALDataType bufType=(GDALDataType) 0,int band_list=0,int *pband_list=0,int nPixelSpace=0,int nLineSpace=0,int nBandSpace=0,char **options=0){

    if ((options != NULL) && (buf_xsize ==0) && (buf_ysize == 0))
    {

        const char* pszLevel = CSLFetchNameValue(options, "LEVEL");
        if (pszLevel)
        {

            int nLevel = atoi(pszLevel);
            int nRes = 2 << (nLevel - 1);
            buf_xsize = ceil(xSize / (1.0 * nRes));
            buf_ysize = ceil(ySize / (1.0 * nRes));
        }
    }

    int nxsize = (buf_xsize == 0) ? xSize : buf_xsize;
    int nysize = (buf_ysize == 0) ? ySize : buf_ysize;

    GDALDataType ntype;
    if (bufType != 0) {
        ntype = (GDALDataType) bufType;
    }
    else {
        ntype = GDT_Byte;
    }

    int nBCount = (band_list) != 0 ? band_list : GDALGetRasterCount(self);
    int nMinSize = nxsize * nysize * nBCount * (GDALGetDataTypeSize(ntype) / 8);
    if (buf_string == NULL || buf_len < nMinSize)
    {
        CPLError(CE_Failure, CPLE_AppDefined, "Buffer is too small");
        return NULL;
    }

    bool myBandList = false;
    int* pBandList;

    if (band_list != 0){
        myBandList = false;
        pBandList = pband_list;
    }
    else
    {
        myBandList = true;
        pBandList = (int*)CPLMalloc(sizeof(int) * nBCount);
        for (int i = 0; i < nBCount; ++i) {
            pBandList[i] = i + 1;
        }
    }

    GDALAsyncReaderH hAsyncReader =
            GDALBeginAsyncReader(self, xOff, yOff, xSize, ySize, (void*) buf_string, nxsize, nysize, ntype, nBCount, pBandList, nPixelSpace, nLineSpace,
    nBandSpace, options);
    if (hAsyncReader)
    {
        return (GDALAsyncReader*) CreateAsyncReaderWrapper(hAsyncReader, pyObject);
    }
    else
    {
        return NULL;
    }

    if ( myBandList ) {
       CPLFree( pBandList );
    }

  }
