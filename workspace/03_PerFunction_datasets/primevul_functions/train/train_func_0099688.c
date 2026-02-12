static bool zlibToDataBuf(const byte* bytes,long length, DataBuf& result)
    {
        uLongf uncompressedLen = length * 2;
        int    zlibResult;

        do {
            result.alloc(uncompressedLen);
            zlibResult = uncompress((Bytef*)result.pData_,&uncompressedLen,bytes,length);

            if (zlibResult == Z_OK && (long) uncompressedLen < result.size_ ) {
                result.free();

                result.alloc(uncompressedLen);
                zlibResult = uncompress((Bytef*)result.pData_,&uncompressedLen,bytes,length);
            }
            if (zlibResult == Z_BUF_ERROR) {

                result.free();


                if  (uncompressedLen > 16*1024*1024) zlibResult = Z_DATA_ERROR;
                else uncompressedLen *= 2;
            }
        } while (zlibResult == Z_BUF_ERROR);

        return zlibResult == Z_OK ;
    }
