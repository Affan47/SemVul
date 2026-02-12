UnicodeString::doHashCode() const
{


    int32_t hashCode = ustr_hashUCharsN(getArrayStart(), length());
    if (hashCode == kInvalidHashCode) {
        hashCode = kEmptyHashCode;
    }
    return hashCode;
}
