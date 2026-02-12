uint32_t TiffImageEntry::doWriteData(IoWrapper& ioWrapper,
                                         ByteOrder byteOrder,
                                         int32_t   ,
                                         uint32_t  ,
                                         uint32_t& ) const
    {
        uint32_t len = 0;

        if (group() > mnId) {
            len = writeImage(ioWrapper, byteOrder);
        }
        return len;
    }
