decodeCachedValue(unsigned int &value,
                                    unsigned int numBits,
                                    IntCache     &cache,
                                    unsigned int blockSize,
                                    int          endOkay)
{
    unsigned int index;

    DBG("decodeIntCache.\n");

    if (!countLeadingZeros(index, endOkay))
    {
        return 0;
    }

    if (index == 2)
    {
        unsigned int sameDiff;

        decodeDirect(sameDiff, 1);

        if (sameDiff)
        {
            value = cache.getLastDiff(PARTIAL_INT_MASK[numBits]);
            cache.insert(value, PARTIAL_INT_MASK[numBits]);
            return 1;
        }

        blockSize = cache.getBlockSize(numBits);

        if (!decodeValue(value, numBits, blockSize, endOkay))
        {
            return 0;
        }

        cache.insert(value, PARTIAL_INT_MASK[numBits]);
        return 1;
    }

    if (index > 2)
        index--;
    if (index > cache.getSize())
    {
        CERR << "Assertion 2 failed in DecodeCachedValue: index=" << index
            << ", cache size=" << cache.getSize() << ENDL;
        abort();
    }
    value = cache.get(index);
    return 1;
}
