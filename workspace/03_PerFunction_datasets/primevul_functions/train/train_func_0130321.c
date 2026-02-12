unfold_and_compact_mime_header(const char *lines, gint *first_colon_offset)
{
    const char *p = lines;
    char c;
    char *ret, *q;
    char sep_seen = 0;
    char lws = FALSE;
    gint colon = -1;

    if (! lines) return NULL;

    c = *p;
    ret = (char *)wmem_alloc(wmem_packet_scope(), strlen(lines) + 1);
    q = ret;

    while (c) {
        if (c == ':') {
            lws = FALSE;
            if (colon == -1) {
                colon = (gint) (q - ret);
            }
            *(q++) = sep_seen = c;
            p++;
        } else if (c == ';' || c == ',' || c == '=') {
            lws = FALSE;
            *(q++) = sep_seen = c;
            p++;
        } else if (c == ' ' || c == '\t') {
            lws = TRUE;
            p++;
        } else if (c == '\n') {
            lws = FALSE;
            if ((c = *(p+1))) {
                if (c == ' ' || c == '\t') {
                    lws = TRUE;
                    p += 2;
                } else {
                    *q = c = 0;
                }
            }
        } else if (c == '\r') {
            lws = FALSE;
            if ((c = *(p+1))) {
                if (c == '\n') {
                    if ((c = *(p+2))) {
                        if (c == ' ' || c == '\t') {
                            lws = TRUE;
                            p += 3;
                        } else {
                            *q = c = 0;
                        }
                    }
                } else if (c == ' ' || c == '\t') {
                    lws = TRUE;
                    p += 2;
                } else {
                    *q = c = 0;
                }
            }
        } else if (c == '"') {
            lws = FALSE;
            *(q++) = c;
            while (c) {
                c = *(q++) = *(++p);
                if (c == '\\') {


                    c = *(q++) = *(++p);
                } else {
                    if (c == '"') {
                        p++;
                        break;
                    }
                }
            }

            if(c == 0) {
                q--;
            }
        } else {
            if (sep_seen) {
                sep_seen = 0;
            } else {
                if (lws) {
                    *(q++) = ' ';
                }
            }
            lws = FALSE;
            *(q++) = c;
            p++;
        }

        if (c) {
            c = *p;
        }
    }
    *q = 0;

    *first_colon_offset = colon;
    return (ret);
}
