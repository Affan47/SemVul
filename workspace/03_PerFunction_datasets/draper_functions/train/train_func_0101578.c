getThisAppSeg()
{
    if ( mAppSeg && (mAppSeg->isRaw()))
    {


        std::string id ;
        ExifAppSegment::createAppId(mAppSeg->getAppSegmentMarker(),
                                    mAppSeg->getAppIdent(), id ) ;
        ExifAppSegment* tempAppSeg = ExifAppSegment::create( id, false ) ;
        if ( tempAppSeg )
        {


            ExifRawAppSeg* rawAppSeg = dynamic_cast<ExifRawAppSeg*>(mAppSeg) ;
            if ( rawAppSeg )
            {
                ExifStatus status ;
                char * rawAppSegData = rawAppSeg->getRawData() ;
                ExifIO* exifio = new ExifIO( status, rawAppSegData,
                    rawAppSeg->getLength(), "r+", rawAppSeg->getLength() ) ;
                if ( status == EXIF_OK )
                {


                    int i = 2 ;
                    while( rawAppSegData[i] != '\0' ) i++ ;
                    i++;
                    if ( tempAppSeg->isTiff() )
                        while( rawAppSegData[i] == '\0' ) i++ ;
                    exifio->seek( i, SEEK_SET ) ;
                    status = tempAppSeg->init(exifio,rawAppSeg->getLength(),i) ;

                    if ( status == EXIF_OK )
                    {


                        ExifAppSegment * tmp = mAppSeg ;
                        mAppSeg = tempAppSeg ;
                        tempAppSeg = tmp;
                    }
                }
                delete exifio ;
            }
            delete tempAppSeg ;
        }


        mIsConverted = true ;
    }

    return mAppSeg ;
}
