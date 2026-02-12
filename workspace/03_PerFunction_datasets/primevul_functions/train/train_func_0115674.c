uint32_t TiffSubIfd::doWrite(IoWrapper& ioWrapper,
                                 ByteOrder byteOrder,
                                 int32_t   offset,
                                 uint32_t  ,
                                 uint32_t  dataIdx,
                                 uint32_t& )
    {
        DataBuf buf(static_cast<long>(ifds_.size()) * 4);
        uint32_t idx = 0;

        std::sort(ifds_.begin(), ifds_.end(), cmpGroupLt);
        for (Ifds::const_iterator i = ifds_.begin(); i != ifds_.end(); ++i) {
            idx += writeOffset(buf.pData_ + idx, offset + dataIdx, tiffType(), byteOrder);
            dataIdx += (*i)->size();
        }
        ioWrapper.write(buf.pData_, buf.size_);
        return (uint32_t)buf.size_;
    }
