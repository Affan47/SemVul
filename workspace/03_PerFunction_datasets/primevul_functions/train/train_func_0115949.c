size_t Nikon2MnHeader::write(IoWrapper& ioWrapper,
                                   ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
