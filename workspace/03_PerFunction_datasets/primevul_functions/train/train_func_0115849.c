size_t Casio2MnHeader::write(IoWrapper& ioWrapper,
                                 ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
