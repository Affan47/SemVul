uint32_t CiffEntry::doWrite(Blob&     blob,
                                ByteOrder ,
                                uint32_t  offset)
    {
        return writeValueData(blob, offset);
    }
