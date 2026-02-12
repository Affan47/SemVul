size_t SonyMnHeader::write(IoWrapper& ioWrapper,
                                 ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
