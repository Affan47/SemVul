size_t FujiMnHeader::write(IoWrapper& ioWrapper,
                                 ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
