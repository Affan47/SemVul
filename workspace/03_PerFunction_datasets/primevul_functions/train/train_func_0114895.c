uint32_t TiffDataEntry::doWriteData(IoWrapper& ioWrapper,
                                        ByteOrder ,
                                        int32_t   ,
                                        uint32_t  ,
                                        uint32_t& ) const
    {
        if (!pValue()) return 0;

        DataBuf buf = pValue()->dataArea();
        ioWrapper.write(buf.pData_, buf.size_);

        uint32_t align = (buf.size_ & 1);
        if (align) ioWrapper.putb(0x0);

        return (uint32_t)buf.size_ + align;
    }
