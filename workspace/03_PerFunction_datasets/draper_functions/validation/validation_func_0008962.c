compare(UCharIterator &sIter,
                                            UCharIterator &tIter,
                                            UErrorCode &status) const {
    if(U_SUCCESS(status)) {
        return ucol_strcollIter(ucollator, &sIter, &tIter, &status);
    } else {
        return UCOL_EQUAL;
    }
}
