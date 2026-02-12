size_t PentaxMnHeader::write(IoWrapper& ioWrapper,
                                   ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
