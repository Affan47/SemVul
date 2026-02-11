open(fhandle_t fileHandle, const char* name,
                              const char* cmode)
{
    ExifStatus status ;

    mExifio = new ExifIO( status, fileHandle, name, cmode ) ;
    if( status != EXIF_OK )
    {
        delete mExifio ;
        mExifio = NULL ;
    }
    else
    {
        mFileName = name ;
        mIOwnExifIO = true ;
        status = initAfterOpen( cmode ) ;
    }

    return status ;
}
