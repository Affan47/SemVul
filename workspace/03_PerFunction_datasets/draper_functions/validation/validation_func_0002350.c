find(const UnicodeString& text, int32_t start, uint32_t types, UErrorCode& status) const {
    ZNameSearchHandler handler(types);

    TimeZoneNamesImpl *nonConstThis = const_cast<TimeZoneNamesImpl *>(this);

    umtx_lock(&gLock);
    {
        fNamesTrie.search(text, start, (TextTrieMapSearchResultHandler *)&handler, status);
    }
    umtx_unlock(&gLock);

    if (U_FAILURE(status)) {
        return NULL;
    }

    int32_t maxLen = 0;
    TimeZoneNames::MatchInfoCollection* matches = handler.getMatches(maxLen);
    if (matches != NULL && ((maxLen == (text.length() - start)) || fNamesTrieFullyLoaded)) {

        return matches;
    }

    delete matches;


    umtx_lock(&gLock);
    {
        if (!fNamesTrieFullyLoaded) {
            const UnicodeString *id;


            StringEnumeration *tzIDs = TimeZone::createTimeZoneIDEnumeration(UCAL_ZONE_TYPE_CANONICAL, NULL, NULL, status);
            if (U_SUCCESS(status)) {
                while ((id = tzIDs->snext(status))) {
                    if (U_FAILURE(status)) {
                        break;
                    }

                    nonConstThis->loadStrings(*id);
                }
            }
            if (tzIDs != NULL) {
                delete tzIDs;
            }
            if (U_SUCCESS(status)) {
                nonConstThis->fNamesTrieFullyLoaded = TRUE;
            }
        }
    }
    umtx_unlock(&gLock);

    if (U_FAILURE(status)) {
        return NULL;
    }

    umtx_lock(&gLock);
    {

        fNamesTrie.search(text, start, (TextTrieMapSearchResultHandler *)&handler, status);
    }
    umtx_unlock(&gLock);

    return handler.getMatches(maxLen);
}
