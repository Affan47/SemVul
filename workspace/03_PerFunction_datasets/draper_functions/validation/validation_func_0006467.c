operator=(const DateTimePatternGenerator& other) {
    pLocale = other.pLocale;
    fDefaultHourFormatChar = other.fDefaultHourFormatChar;
    *fp = *(other.fp);
    dtMatcher->copyFrom(other.dtMatcher->skeleton);
    *distanceInfo = *(other.distanceInfo);
    dateTimeFormat = other.dateTimeFormat;
    decimal = other.decimal;

    dateTimeFormat.getTerminatedBuffer();
    decimal.getTerminatedBuffer();
    delete skipMatcher;
    if ( other.skipMatcher == NULL ) {
        skipMatcher = NULL;
    }
    else {
        skipMatcher = new DateTimeMatcher(*other.skipMatcher);
    }
    for (int32_t i=0; i< UDATPG_FIELD_COUNT; ++i ) {
        appendItemFormats[i] = other.appendItemFormats[i];
        appendItemNames[i] = other.appendItemNames[i];

        appendItemFormats[i].getTerminatedBuffer();
        appendItemNames[i].getTerminatedBuffer();
    }
    UErrorCode status = U_ZERO_ERROR;
    patternMap->copyFrom(*other.patternMap, status);
    copyHashtable(other.fAvailableFormatKeyHash, status);
    return *this;
}
