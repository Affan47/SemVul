onlyWhitespace(const char* s)
{
    size_t len = strlen(s);
    int charsFound = OFFalse;

    for (size_t i = 0; (!charsFound) && (i < len); ++i) {
        charsFound = !isspace(OFstatic_cast(unsigned char, s[i]));
    }
    return (!charsFound)? (OFTrue) : (OFFalse);
}
