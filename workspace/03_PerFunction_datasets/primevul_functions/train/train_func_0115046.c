size_t Olympus2MnHeader::write(IoWrapper& ioWrapper,
                                    ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
