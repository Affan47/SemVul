size_t PentaxDngMnHeader::write(IoWrapper& ioWrapper,
                                   ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
