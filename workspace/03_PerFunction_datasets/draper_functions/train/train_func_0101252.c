setLocale(const Locale& loc, UErrorCode& status) {
    if (U_FAILURE(status)) {
        return;
    }
    locale = loc;
    msgPattern.clear();
    delete numberFormat;
    offset = 0;
    numberFormat = NULL;
    pluralRulesWrapper.reset();
    init(NULL, UPLURAL_TYPE_CARDINAL, status);
}
