static int parse_ranges(const char *hdr, unsigned long len,
                        struct range **ranges)
{
    int ret = HTTP_BAD_RANGE;
    struct range *new, *tail = *ranges = NULL;
    tok_t tok;
    char *token;

    if (!len) return HTTP_OK;


    if (!hdr || strncmp(hdr, "bytes=", 6)) return HTTP_OK;

    tok_init(&tok, hdr+6, ",", TOK_TRIMLEFT|TOK_TRIMRIGHT);
    while ((token = tok_next(&tok))) {

        unsigned long first = 0;
        unsigned long last = len - 1;
        char *p, *endp;

        if (!(p = strchr(token, '-'))) continue;

        if (p == token) {

            unsigned long suffix = strtoul(++p, &endp, 10);

            if (endp == p || *endp) continue;
            if (!suffix) continue;


            if (suffix < len) first = len - suffix;
        }
        else {

            first = strtoul(token, &endp, 10);
            if (endp != p) continue;
            if (first >= len) continue;

            if (*++p) {

                last = strtoul(p, &endp, 10);
                if (*endp || last < first) continue;


                if (last >= len) last = len - 1;
            }
        }

        ret = HTTP_PARTIAL;


        if (tail &&
            first >= tail->first && (long) (first - tail->last) < 80) {
            tail->last = MAX(last, tail->last);
            continue;
        }


        new = xzmalloc(sizeof(struct range));
        new->first = first;
        new->last = last;

        if (tail) tail->next = new;
        else *ranges = new;
        tail = new;
    }

    tok_fini(&tok);

    return ret;
}
