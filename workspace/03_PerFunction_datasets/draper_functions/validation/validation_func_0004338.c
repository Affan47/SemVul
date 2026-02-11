setAllowedLocales(const char *localesList, UErrorCode &status) {
    UnicodeSet    allowedChars;
    UnicodeSet    *tmpSet = NULL;
    const char    *locStart = localesList;
    const char    *locEnd = NULL;
    const char    *localesListEnd = localesList + uprv_strlen(localesList);
    int32_t        localeListCount = 0;


    do {
        locEnd = uprv_strchr(locStart, ',');
        if (locEnd == NULL) {
            locEnd = localesListEnd;
        }
        while (*locStart == ' ') {
            locStart++;
        }
        const char *trimmedEnd = locEnd-1;
        while (trimmedEnd > locStart && *trimmedEnd == ' ') {
            trimmedEnd--;
        }
        if (trimmedEnd <= locStart) {
            break;
        }
        const char *locale = uprv_strndup(locStart, trimmedEnd + 1 - locStart);
        localeListCount++;


        addScriptChars(locale, &allowedChars, status);
        uprv_free((void *)locale);
        if (U_FAILURE(status)) {
            break;
        }
        locStart = locEnd + 1;
    } while (locStart < localesListEnd);


    if (localeListCount == 0) {
        uprv_free((void *)fAllowedLocales);
        fAllowedLocales = uprv_strdup("");
        tmpSet = new UnicodeSet(0, 0x10ffff);
        if (fAllowedLocales == NULL || tmpSet == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return;
        }
        tmpSet->freeze();
        delete fAllowedCharsSet;
        fAllowedCharsSet = tmpSet;
        fCheckMask &= ~USPOOF_CHAR_LIMIT;
        return;
    }


    UnicodeSet tempSet;
    tempSet.applyIntPropertyValue(UCHAR_SCRIPT, USCRIPT_COMMON, status);
    allowedChars.addAll(tempSet);
    tempSet.applyIntPropertyValue(UCHAR_SCRIPT, USCRIPT_INHERITED, status);
    allowedChars.addAll(tempSet);


    if (U_FAILURE(status)) {
        return;
    }


    tmpSet = static_cast<UnicodeSet *>(allowedChars.clone());
    const char *tmpLocalesList = uprv_strdup(localesList);
    if (tmpSet == NULL || tmpLocalesList == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return;
    }
    uprv_free((void *)fAllowedLocales);
    fAllowedLocales = tmpLocalesList;
    tmpSet->freeze();
    delete fAllowedCharsSet;
    fAllowedCharsSet = tmpSet;
    fCheckMask |= USPOOF_CHAR_LIMIT;
}
