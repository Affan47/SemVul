isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd) {
    int length = trailingBytesForUTF8[*source]+1;
    if (source+length > sourceEnd) {
        return false;
    }
    return isLegalUTF8(source, length);
}
