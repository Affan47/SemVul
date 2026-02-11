forData(const CollationData *d, UErrorCode &ec) {
    if(U_FAILURE(ec)) { return; }
    errorCode = ec;

    if(d->base != NULL) {
        checkTailored = -1;
    }
    data = d;
    utrie2_enum(data->trie, NULL, enumCnERange, this);
    if(d->base == NULL || U_FAILURE(errorCode)) {
        ec = errorCode;
        return;
    }

    tailored.freeze();
    checkTailored = 1;
    data = d->base;
    utrie2_enum(data->trie, NULL, enumCnERange, this);
    ec = errorCode;
}
