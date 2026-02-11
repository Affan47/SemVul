IDtoSTV(const UnicodeString& id,
                                     UnicodeString& source,
                                     UnicodeString& target,
                                     UnicodeString& variant,
                                     UBool& isSourcePresent) {
    source = ANY;
    target.truncate(0);
    variant.truncate(0);

    int32_t sep = id.indexOf(TARGET_SEP);
    int32_t var = id.indexOf(VARIANT_SEP);
    if (var < 0) {
        var = id.length();
    }
    isSourcePresent = FALSE;

    if (sep < 0) {

        id.extractBetween(0, var, target);
        id.extractBetween(var, id.length(), variant);
    } else if (sep < var) {

        if (sep > 0) {
            id.extractBetween(0, sep, source);
            isSourcePresent = TRUE;
        }
        id.extractBetween(++sep, var, target);
        id.extractBetween(var, id.length(), variant);
    } else {

        if (var > 0) {
            id.extractBetween(0, var, source);
            isSourcePresent = TRUE;
        }
        id.extractBetween(var, sep++, variant);
        id.extractBetween(sep, id.length(), target);
    }

    if (variant.length() > 0) {
        variant.remove(0, 1);
    }
}
