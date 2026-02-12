long IptcData::size() const
    {
        size_t newSize = 0;
        const_iterator iter = iptcMetadata_.begin();
        const_iterator end = iptcMetadata_.end();
        for ( ; iter != end; ++iter) {

            newSize += 5;
            size_t dataSize = iter->size();
            newSize += dataSize;
            if (dataSize > 32767) {

                newSize += 4;
            }
        }
        return (long)newSize;
    }
