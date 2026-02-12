STATIC bool
S_new_regcurly(const char *s, const char *e)
{


    bool has_min = FALSE;
    bool has_max = FALSE;

    PERL_ARGS_ASSERT_NEW_REGCURLY;

    if (s >= e || *s++ != '{')
	return FALSE;

    while (s < e && isSPACE(*s)) {
        s++;
    }
    while (s < e && isDIGIT(*s)) {
        has_min = TRUE;
        s++;
    }
    while (s < e && isSPACE(*s)) {
        s++;
    }

    if (*s == ',') {
	s++;
        while (s < e && isSPACE(*s)) {
            s++;
        }
        while (s < e && isDIGIT(*s)) {
            has_max = TRUE;
            s++;
        }
        while (s < e && isSPACE(*s)) {
            s++;
        }
    }

    return s < e && *s == '}' && (has_min || has_max);
}
