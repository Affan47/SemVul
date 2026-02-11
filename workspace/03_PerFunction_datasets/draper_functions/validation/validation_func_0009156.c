create(const Locale& locale,
                           DateIntervalInfo* dtitvinf,
                           const UnicodeString* skeleton,
                           UErrorCode& status) {
    DateIntervalFormat* f = new DateIntervalFormat(locale, dtitvinf,
                                                   skeleton, status);
    if ( f == NULL ) {
        status = U_MEMORY_ALLOCATION_ERROR;
        delete dtitvinf;
    } else if ( U_FAILURE(status) ) {

        delete f;
        f = 0;
    }
    return f;
}
