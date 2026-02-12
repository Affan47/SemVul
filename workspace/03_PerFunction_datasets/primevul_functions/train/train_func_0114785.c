TiffComponent* newNikonMn(uint16_t    tag,
                              IfdId       group,
                              IfdId       ,
                              const byte* pData,
                              uint32_t    size,
                              ByteOrder   )
    {

        if (size < 6 ||    std::string(reinterpret_cast<const char*>(pData), 6)
                        != std::string("Nikon\0", 6)) {

            if (size < 18) return 0;
            return newIfdMn2(tag, group, nikon1Id);
        }


        TiffHeader tiffHeader;
        if (   size < 18
            || !tiffHeader.read(pData + 10, size - 10)
            || tiffHeader.tag() != 0x002a) {

            if (size < Nikon2MnHeader::sizeOfSignature() + 18) return 0;
            return newNikon2Mn2(tag, group, nikon2Id);
        }


        if (size < Nikon3MnHeader::sizeOfSignature() + 18) return 0;
        return newNikon3Mn2(tag, group, nikon3Id);
    }
