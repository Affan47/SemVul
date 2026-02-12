size_t PanasonicMnHeader::write(IoWrapper& ioWrapper,
                                      ByteOrder ) const
    {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
