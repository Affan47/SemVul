size_t OlympusMnHeader::write(IoWrapper& ioWrapper,
                                    ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
