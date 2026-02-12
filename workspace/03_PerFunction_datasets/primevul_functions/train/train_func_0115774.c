uint32_t TiffDirectory::doWrite(IoWrapper& ioWrapper,
                                    ByteOrder byteOrder,
                                    int32_t   offset,
                                    uint32_t  valueIdx,
                                    uint32_t  dataIdx,
                                    uint32_t& imageIdx)
    {
        bool isRootDir = (imageIdx == uint32_t(-1));


        const uint32_t compCount = count();
        if (compCount > 0xffff) throw Error(kerTooManyTiffDirectoryEntries, groupName(group()));


        uint32_t sizeNext = 0;
        if (pNext_) sizeNext = pNext_->size();


        if (compCount == 0 && sizeNext == 0) return 0;


        if (group() == ifd3Id) {
#ifdef DEBUG
            std::cerr << "Directory " << groupName(group()) << " offset is 0x"
                      << std::setw(8) << std::setfill('0') << std::hex << offset << std::dec
                      << "\n";
#endif
            ioWrapper.setTarget(OffsetWriter::cr2RawIfdOffset, offset);
        }

        const uint32_t sizeDir = 2 + 12 * compCount + (hasNext_ ? 4 : 0);


        if (group() < mnId) {
            std::sort(components_.begin(), components_.end(), cmpTagLt);
        }

        uint32_t sizeValue = 0;
        uint32_t sizeData = 0;
        for (Components::const_iterator i = components_.begin(); i != components_.end(); ++i) {
            uint32_t sv = (*i)->size();
            if (sv > 4) {
                sv += sv & 1;
                sizeValue += sv;
            }

            if (isRootDir) {
                uint32_t sd = (*i)->sizeData();
                sd += sd & 1;
                sizeData += sd;
            }
        }

        uint32_t idx = 0;
        valueIdx = sizeDir;
        dataIdx  = sizeDir + sizeValue;
        if (isRootDir) {
            imageIdx = offset + dataIdx + sizeData + sizeNext;
            imageIdx += imageIdx & 1;
        }


        byte buf[4];
        us2Data(buf, static_cast<uint16_t>(compCount), byteOrder);
        ioWrapper.write(buf, 2);
        idx += 2;

        for (Components::const_iterator i = components_.begin(); i != components_.end(); ++i) {
            idx += writeDirEntry(ioWrapper, byteOrder, offset, *i, valueIdx, dataIdx, imageIdx);
            uint32_t sv = (*i)->size();
            if (sv > 4) {
                sv += sv & 1;
                valueIdx += sv;
            }
            uint32_t sd = (*i)->sizeData();
            sd += sd & 1;
            dataIdx += sd;
        }

        if (hasNext_) {
            memset(buf, 0x0, 4);
            if (pNext_ && sizeNext) {
                l2Data(buf, offset + dataIdx, byteOrder);
            }
            ioWrapper.write(buf, 4);
            idx += 4;
        }
        assert(idx == sizeDir);


        valueIdx = sizeDir;
        dataIdx = sizeDir + sizeValue;
        for (Components::const_iterator i = components_.begin(); i != components_.end(); ++i) {
            uint32_t sv = (*i)->size();
            if (sv > 4) {
                uint32_t d = (*i)->write(ioWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx);
                enforce(sv == d, kerImageWriteFailed);
                if ((sv & 1) == 1) {
                    ioWrapper.putb(0x0);
                    sv += 1;
                }
                idx += sv;
                valueIdx += sv;
            }
            uint32_t sd = (*i)->sizeData();
            sd += sd & 1;
            dataIdx += sd;
        }
        assert(idx == sizeDir + sizeValue);


        dataIdx = sizeDir + sizeValue;
        idx += writeData(ioWrapper, byteOrder, offset, dataIdx, imageIdx);


        if (pNext_ && sizeNext) {
            idx += pNext_->write(ioWrapper, byteOrder, offset + idx, uint32_t(-1), uint32_t(-1), imageIdx);
        }


        if (isRootDir) {
            idx += writeImage(ioWrapper, byteOrder);
        }

        return idx;
    }
