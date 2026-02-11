strcasechr(const char *haystack, register const char needle)
{
    register const char *t;

    REQUIRE_RVAL(haystack != SPIF_NULL_TYPE(ptr), SPIF_NULL_TYPE(ptr));
    for (t = haystack; t && *t; t++) {
        if (tolower(*t) == tolower(needle)) {
            return ((char *) t);
        }
    }
    return (NULL);
}
