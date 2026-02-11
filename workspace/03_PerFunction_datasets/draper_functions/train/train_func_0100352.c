getDateTimePattern(
        const UResourceBundle *resource,
        UnicodeString &result,
        UErrorCode &status) {
    UnicodeString defaultCalendarName;
    if (!getStringWithFallback(
            resource,
            "calendar/default",
            defaultCalendarName,
            status)) {
        return FALSE;
    }
    CharString pathBuffer;
    pathBuffer.append("calendar/", status)
            .appendInvariantChars(defaultCalendarName, status)
            .append("/DateTimePatterns", status);
    LocalUResourceBundlePointer topLevel(
            ures_getByKeyWithFallback(
                    resource, pathBuffer.data(), NULL, &status));
    if (U_FAILURE(status)) {
        return FALSE;
    }
    int32_t size = ures_getSize(topLevel.getAlias());
    if (size <= 8) {


        result = UNICODE_STRING_SIMPLE("{1} {0}");
        return TRUE;
    }
    return getStringByIndex(topLevel.getAlias(), 8, result, status);
}
