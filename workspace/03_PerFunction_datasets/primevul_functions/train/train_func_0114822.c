size_t Nikon3MnHeader::write(IoWrapper& ioWrapper, ByteOrder byteOrder) const
    {
        assert(buf_.size_ >= 10);

        ioWrapper.write(buf_.pData_, 10);


        TiffHeader th(byteOrder);
        DataBuf buf = th.write();
        ioWrapper.write(buf.pData_, buf.size_);
        return 10 + buf.size_;
    }
