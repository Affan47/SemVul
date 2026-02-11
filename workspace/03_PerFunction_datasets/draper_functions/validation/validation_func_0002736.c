createInstance(TimeZone* zone, const Locale& aLocale, UErrorCode& success)
{
    if (U_FAILURE(success)) {
        return NULL;
    }

    Locale actualLoc;
    UObject* u = NULL;

#if !UCONFIG_NO_SERVICE
    if (isCalendarServiceUsed()) {
        u = getCalendarService(success)->get(aLocale, LocaleKey::KIND_ANY, &actualLoc, success);
    }
    else
#endif
    {
        u = createStandardCalendar(getCalendarTypeForLocale(aLocale.getName()), aLocale, success);
    }
    Calendar* c = NULL;

    if(U_FAILURE(success) || !u) {
        delete zone;
        if(U_SUCCESS(success)) {
            success = U_INTERNAL_PROGRAM_ERROR;
        }
        return NULL;
    }

#if !UCONFIG_NO_SERVICE
    const UnicodeString* str = dynamic_cast<const UnicodeString*>(u);
    if(str != NULL) {


        Locale l("");
        LocaleUtility::initLocaleFromName(*str, l);

#ifdef U_DEBUG_CALSVC
        fprintf(stderr, "Calendar::createInstance(%s), looking up [%s]\n", aLocale.getName(), l.getName());
#endif

        Locale actualLoc2;
        delete u;
        u = NULL;


        c = (Calendar*)getCalendarService(success)->get(l, LocaleKey::KIND_ANY, &actualLoc2, success);

        if(U_FAILURE(success) || !c) {
            delete zone;
            if(U_SUCCESS(success)) {
                success = U_INTERNAL_PROGRAM_ERROR;
            }
            return NULL;
        }

        str = dynamic_cast<const UnicodeString*>(c);
        if(str != NULL) {


#ifdef U_DEBUG_CALSVC
            char tmp[200];

            int32_t len = str->length();
            int32_t actLen = sizeof(tmp)-1;
            if(len > actLen) {
                len = actLen;
            }
            str->extract(0,len,tmp);
            tmp[len]=0;

            fprintf(stderr, "err - recursed, 2nd lookup was unistring %s\n", tmp);
#endif
            success = U_MISSING_RESOURCE_ERROR;
            delete c;
            delete zone;
            return NULL;
        }
#ifdef U_DEBUG_CALSVC
        fprintf(stderr, "%p: setting week count data to locale %s, actual locale %s\n", c, (const char*)aLocale.getName(), (const char *)actualLoc.getName());
#endif
        c->setWeekData(aLocale, c->getType(), success);
    }
    else
#endif
    {

        c = (Calendar*)u;
    }


    c->adoptTimeZone(zone);
    c->setTimeInMillis(getNow(), success);

    return c;
}
