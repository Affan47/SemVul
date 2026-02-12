TiffComponent* newPanasonicMn(uint16_t    tag,
                                  IfdId       group,
                                  IfdId       mnGroup,
                                  const byte* ,
                                  uint32_t    size,
                                  ByteOrder   )
    {

        if (size < PanasonicMnHeader::sizeOfSignature() + 14) return 0;
        return newPanasonicMn2(tag, group, mnGroup);
    }
