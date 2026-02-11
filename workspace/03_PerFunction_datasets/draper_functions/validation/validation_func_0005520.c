cx_debug_parse_string(const cxchar *string, const cx_debug_key *keys,
                      cxuint nkeys)
{

    cxuint i;
    cxuint result = 0;


    if (string == 0)
        return 0;

    if (!cx_strcasecmp(string, "all")) {
        for (i = 0; i < nkeys; i++)
            result |= keys[i].value;
    }
    else {

        const cxchar *p = string;
        const cxchar *q;
        cxbool done = FALSE;

        while (*p && !done) {
            q = strchr(p, ':');

            if (!q) {
                q = p + strlen(p);
                done = TRUE;
            }

            for (i = 0; i < nkeys; i++) {
                if (cx_strncasecmp(keys[i].key, p, q - p) == 0 &&
                    keys[i].key[q - p] == '\0')
                    result |= keys[i].value;
            }
        }
    }

    return result;

}
