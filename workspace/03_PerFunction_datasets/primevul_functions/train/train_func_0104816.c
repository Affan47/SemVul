static char *line_from_stdmac(void)
{
    unsigned char c;
    const unsigned char *p = stdmacpos;
    char *line, *q;
    size_t len = 0;

    if (!stdmacpos)
        return NULL;


    while ((c = *p++) != 127) {
        uint8_t ndir = c - 128;
        if (ndir < 256-96)
            len += pp_directives_len[ndir] + 1;
        else
            len++;
    }

    line = nasm_malloc(len + 1);
    q = line;

    while ((c = *stdmacpos++) != 127) {
        uint8_t ndir = c - 128;
        if (ndir < 256-96) {
            memcpy(q, pp_directives[ndir], pp_directives_len[ndir]);
            q += pp_directives_len[ndir];
            *q++ = ' ';
        } else {
            *q++ = c;
        }
    }
    stdmacpos = p;
    *q = '\0';

    if (*stdmacpos == 127) {

        stdmacpos = NULL;
        if (*stdmacnext) {
            stdmacpos = *stdmacnext++;
        } else if (do_predef) {
            Line *pd, *l;


            list_for_each(pd, predef) {
                nasm_new(l);
                l->next     = istk->expansion;
                l->first    = dup_tlist(pd->first, NULL);
                l->finishes = NULL;

                istk->expansion = l;
            }
            do_predef = false;
        }
    }

    return line;
}
