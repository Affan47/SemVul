checkConsistency(EStyle style, const char* key, UErrorCode& err) {
    if (U_FAILURE(err)) {
        return;
    }


    StringEnumeration* keywords = fPluralRules->getKeywords(err);
    if (U_SUCCESS(err)) {
        const char* pluralCount;
        while ((pluralCount = keywords->next(NULL, err)) != NULL) {
            if ( U_SUCCESS(err) ) {
                for (int32_t i = 0; i < TimeUnit::UTIMEUNIT_FIELD_COUNT; ++i) {


                    Hashtable* countToPatterns = fTimeUnitToCountToPatterns[i];
                    if ( countToPatterns == NULL ) {
                        countToPatterns = initHash(err);
                        if (U_FAILURE(err)) {
                            delete countToPatterns;
                            return;
                        }
                        fTimeUnitToCountToPatterns[i] = countToPatterns;
                    }
                    MessageFormat** formatters = (MessageFormat**)countToPatterns->get(pluralCount);
                    if( formatters == NULL || formatters[style] == NULL ) {

                        const char* localeName = fLocale.getName();
                        searchInLocaleChain(style, key, localeName,
                                            (TimeUnit::UTimeUnitFields)i,
                                            pluralCount, pluralCount,
                                            countToPatterns, err);
                    }
                }
            }
        }
    }
    delete keywords;
}
