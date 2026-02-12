TiffComponent* newIfdMn(uint16_t    tag,
                            IfdId       group,
                            IfdId       mnGroup,
                            const byte* ,
                            uint32_t    size,
                            ByteOrder   )
    {

        if (size < 14) return 0;
        return newIfdMn2(tag, group, mnGroup);
    }
