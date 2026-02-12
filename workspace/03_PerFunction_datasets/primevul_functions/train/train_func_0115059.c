size_t SigmaMnHeader::write(IoWrapper& ioWrapper,
                                  ByteOrder ) const
    {
        ioWrapper.write(signature1_, sizeOfSignature());
        return sizeOfSignature();
    }
