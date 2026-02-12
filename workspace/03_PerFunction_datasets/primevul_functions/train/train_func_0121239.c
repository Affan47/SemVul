void CiffComponent::doRead(const byte* pData,
                               uint32_t    size,
                               uint32_t    start,
                               ByteOrder   byteOrder)
    {

        enforce(size >= 10 && start <= size - 10, kerNotACrwImage);
        tag_ = getUShort(pData + start, byteOrder);

        DataLocId dl = dataLocation();
        assert(dl == directoryData || dl == valueData);

        if (dl == valueData) {
            size_   = getULong(pData + start + 2, byteOrder);
            offset_ = getULong(pData + start + 6, byteOrder);


            if (offset_ < start) {

              enforce(size_ <= start - offset_, kerOffsetOutOfRange);
            } else {

              enforce(offset_ >= start + 10, kerOffsetOutOfRange);
              enforce(offset_ <= size, kerOffsetOutOfRange);
              enforce(size_ <= size - offset_, kerOffsetOutOfRange);
            }
        }
        if (dl == directoryData) {
            size_ = 8;
            offset_ = start + 2;
        }
        pData_ = pData + offset_;
#ifdef EXIV2_DEBUG_MESSAGES
        std::cout << "  Entry for tag 0x"
                  << std::hex << tagId() << " (0x" << tag()
                  << "), " << std::dec << size_
                  << " Bytes, Offset is " << offset_ << "\n";
#endif

    }
