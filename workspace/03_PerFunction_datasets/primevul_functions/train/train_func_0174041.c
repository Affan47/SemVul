bool Jsi_GlobMatch(const char *pattern, const char *string, int nocase)
{
    int c;
    int pchar;
    while (*pattern) {
        switch (pattern[0]) {
            case '*':
                while (pattern[1] == '*') {
                    pattern++;
                }
                pattern++;
                if (!pattern[0]) {
                    return 1;
                }
                while (*string) {
                    if (Jsi_GlobMatch(pattern, string, nocase))
                        return 1;
                    string += Jsi_UtfToUniChar(string, &c);
                }
                return 0;

            case '?':
                string += Jsi_UtfToUniChar(string, &c);
                break;

            case '[': {
                    string += Jsi_UtfToUniChar(string, &c);
                    pattern = JsiCharsetMatch(pattern + 1, c, nocase ? JSI_CMP_NOCASE : 0);
                    if (!pattern) {
                        return 0;
                    }
                    if (!*pattern) {

                        continue;
                    }
                    break;
                }
            case '\\':
                if (pattern[1]) {
                    pattern++;
                }

            default:
                string += Jsi_UtfToUniCharCase(string, &c, nocase);
                Jsi_UtfToUniCharCase(pattern, &pchar, nocase);
                if (pchar != c) {
                    return 0;
                }
                break;
        }
        pattern += Jsi_UtfToUniCharCase(pattern, &pchar, nocase);
        if (!*string) {
            while (*pattern == '*') {
                pattern++;
            }
            break;
        }
    }
    if (!*pattern && !*string) {
        return 1;
    }
    return 0;
}
