SkipToReference(const int& refId) {


    if ( !Rewind() ) return false;


    uint32_t numReferences;
    size_t elementsRead = fread(&numReferences, sizeof(numReferences), 1, m_indexStream);
    if ( elementsRead != 1 ) return false;
    if ( m_isBigEndian ) SwapEndian_32(numReferences);


    bool skippedOk = true;
    int currentRefId = 0;
    while (currentRefId != refId) {
        skippedOk &= LoadReference(currentRefId, false);
        ++currentRefId;
    }


    return skippedOk;
}
