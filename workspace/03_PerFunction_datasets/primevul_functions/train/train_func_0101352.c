static char *line_from_stdmac(void)
{
    unsigned char c;
    const unsigned char *p = stdmacpos;
    char *line, *q;
    size_t len = 0;

    if (!stdmacpos)
        return NULL;

    while ((c = *p++)) {
        if (c >= 0x80)
            len += pp_directives_len[c - 0x80] + 1;
        else
            len++;
    }

    line = nasm_malloc(len + 1);
    q = line;
    while ((c = *stdmacpos++)) {
        if (c >= 0x80) {
            memcpy(q, pp_directives[c - 0x80], pp_directives_len[c - 0x80]);
            q += pp_directives_len[c - 0x80];
            *q++ = ' ';
        } else {
            *q++ = c;
        }
    }
    stdmacpos = p;
    *q = '\0';

    if (!*stdmacpos) {

        stdmacpos = NULL;
        if (*stdmacnext) {
            stdmacpos = *stdmacnext++;
        } else if (do_predef) {
            Line *pd, *l;
            Token *head, **tail, *t;


            list_for_each(pd, predef) {
                head = NULL;
                tail = &head;
                list_for_each(t, pd->first) {
                    *tail = new_Token(NULL, t->type, t->text, 0);
                    tail = &(*tail)->next;
                }

                l           = nasm_malloc(sizeof(Line));
                l->next     = istk->expansion;
                l->first    = head;
                l->finishes = NULL;

                istk->expansion = l;
            }
            do_predef = false;
        }
    }

    return line;
}
