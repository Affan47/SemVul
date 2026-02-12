bool FujiMnHeader::read(const byte* pData,
                            uint32_t size,
                            ByteOrder )
    {
        if (!pData || size < sizeOfSignature()) return false;
        header_.alloc(sizeOfSignature());
        std::memcpy(header_.pData_, pData, header_.size_);


        start_ = getULong(header_.pData_ + 8, byteOrder_);
        if (   static_cast<uint32_t>(header_.size_) < sizeOfSignature()
            || 0 != memcmp(header_.pData_, signature_, 8)) {
            return false;
        }
        return true;
    }
