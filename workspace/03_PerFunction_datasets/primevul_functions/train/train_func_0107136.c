void CrwMap::decode0x2008(const CiffComponent& ciffComponent,
                              const CrwMapping*    ,
                                    Image&         image,
                                    ByteOrder      )
    {
        ExifThumb exifThumb(image.exifData());
        exifThumb.setJpegThumbnail(ciffComponent.pData(), ciffComponent.size());
    }
