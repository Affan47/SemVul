TiffComponent* newSonyMn(uint16_t    tag,
                             IfdId       group,
                             IfdId       ,
                             const byte* pData,
                             uint32_t    size,
                             ByteOrder   )
    {

        if (size < 12 ||   std::string(reinterpret_cast<const char*>(pData), 12)
                        != std::string("SONY DSC \0\0\0", 12)) {

            if (size < 18) return 0;
            return newSony2Mn2(tag, group, sony2Id);
        }

        if (size < SonyMnHeader::sizeOfSignature() + 14) return 0;
        return newSony1Mn2(tag, group, sony1Id);
    }
