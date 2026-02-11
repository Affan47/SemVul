addCanonicalItems() {
    UnicodeString  conflictingPattern;
    UErrorCode status = U_ZERO_ERROR;

    for (int32_t i=0; i<UDATPG_FIELD_COUNT; i++) {
        addPattern(UnicodeString(Canonical_Items[i]), FALSE, conflictingPattern, status);
    }
}
