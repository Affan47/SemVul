TiffComponent* newOlympusMn(uint16_t    tag,
                                IfdId       group,
                                IfdId       ,
                                const byte* pData,
                                uint32_t    size,
                                ByteOrder   )
    {
        if (size < 10 ||   std::string(reinterpret_cast<const char*>(pData), 10)
                        != std::string("OLYMPUS\0II", 10)) {

            if (size < OlympusMnHeader::sizeOfSignature() + 18) return 0;
            return newOlympusMn2(tag, group, olympusId);
        }

        if (size < Olympus2MnHeader::sizeOfSignature() + 18) return 0;
        return newOlympus2Mn2(tag, group, olympus2Id);
    }
