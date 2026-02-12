TiffComponent* newSigmaMn(uint16_t    tag,
                              IfdId       group,
                              IfdId       mnGroup,
                              const byte* ,
                              uint32_t    size,
                              ByteOrder   )
    {

        if (size < SigmaMnHeader::sizeOfSignature() + 18) return 0;
        return newSigmaMn2(tag, group, mnGroup);
    }
