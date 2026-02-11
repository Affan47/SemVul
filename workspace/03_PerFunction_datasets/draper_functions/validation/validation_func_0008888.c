getDisplayName(const TimeZone& tz, UTimeZoneGenericNameType type, UDate date, UnicodeString& name) const {
    name.setToBogus();
    switch (type) {
    case UTZGNM_LOCATION:
        {
            const UChar* tzCanonicalID = ZoneMeta::getCanonicalCLDRID(tz);
            if (tzCanonicalID != NULL) {
                getGenericLocationName(UnicodeString(tzCanonicalID), name);
            }
        }
        break;
    case UTZGNM_LONG:
    case UTZGNM_SHORT:
        formatGenericNonLocationName(tz, type, date, name);
        if (name.isEmpty()) {
            const UChar* tzCanonicalID = ZoneMeta::getCanonicalCLDRID(tz);
            if (tzCanonicalID != NULL) {
                getGenericLocationName(UnicodeString(tzCanonicalID), name);
            }
        }
        break;
    default:
        break;
    }
    return name;
}
