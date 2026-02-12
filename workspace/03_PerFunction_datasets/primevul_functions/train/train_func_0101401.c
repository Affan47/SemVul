static int expand_mmacro(Token * tline)
{
    Token *startline = tline;
    Token *label = NULL;
    int dont_prepend = 0;
    Token **params, *t, *tt;
    MMacro *m;
    Line *l, *ll;
    int i, nparam, *paramlen;
    const char *mname;

    t = tline;
    skip_white_(t);

    if (!tok_type_(t, TOK_ID) && !tok_type_(t, TOK_PREPROC_ID))
        return 0;
    m = is_mmacro(t, &params);
    if (m) {
        mname = t->text;
    } else {
        Token *last;

        label = last = t;
        t = t->next;
        if (tok_type_(t, TOK_WHITESPACE))
            last = t, t = t->next;
        if (tok_is_(t, ":")) {
            dont_prepend = 1;
            last = t, t = t->next;
            if (tok_type_(t, TOK_WHITESPACE))
                last = t, t = t->next;
        }
        if (!tok_type_(t, TOK_ID) || !(m = is_mmacro(t, &params)))
            return 0;
        last->next = NULL;
        mname = t->text;
        tline = t;
    }

    for (nparam = 0; params[nparam]; nparam++) ;
    paramlen = nparam ? nasm_malloc(nparam * sizeof(*paramlen)) : NULL;

    for (i = 0; params[i]; i++) {
        int brace = 0;
        int comma = (!m->plus || i < nparam - 1);

        t = params[i];
        skip_white_(t);
        if (tok_is_(t, "{"))
            t = t->next, brace++, comma = false;
        params[i] = t;
        paramlen[i] = 0;
        while (t) {
            if (comma && t->type == TOK_OTHER && !strcmp(t->text, ","))
                break;
            if (comma && t->type == TOK_WHITESPACE
                && tok_is_(t->next, ","))
                break;
            if (brace && t->type == TOK_OTHER) {
                if (t->text[0] == '{')
                    brace++;
                else if (t->text[0] == '}')
                    if (!--brace)
                        break;
            }
            t = t->next;
            paramlen[i]++;
        }
        if (brace)
            nasm_error(ERR_NONFATAL, "macro params should be enclosed in braces");
    }

    ll = nasm_malloc(sizeof(Line));
    ll->next = istk->expansion;
    ll->finishes = m;
    ll->first = NULL;
    istk->expansion = ll;

    if (m->max_depth && m->in_progress)
        push_mmacro(m);

    m->in_progress ++;
    m->params = params;
    m->iline = tline;
    m->nparam = nparam;
    m->rotate = 0;
    m->paramlen = paramlen;
    m->unique = unique++;
    m->lineno = 0;
    m->condcnt = 0;

    m->next_active = istk->mstk;
    istk->mstk = m;

    list_for_each(l, m->expansion) {
        Token **tail;

        ll = nasm_malloc(sizeof(Line));
        ll->finishes = NULL;
        ll->next = istk->expansion;
        istk->expansion = ll;
        tail = &ll->first;

        list_for_each(t, l->first) {
            Token *x = t;
            switch (t->type) {
            case TOK_PREPROC_Q:
                tt = *tail = new_Token(NULL, TOK_ID, mname, 0);
                break;
            case TOK_PREPROC_QQ:
                tt = *tail = new_Token(NULL, TOK_ID, m->name, 0);
                break;
            case TOK_PREPROC_ID:
                if (t->text[1] == '0' && t->text[2] == '0') {
                    dont_prepend = -1;
                    x = label;
                    if (!x)
                        continue;
                }

            default:
                tt = *tail = new_Token(NULL, x->type, x->text, 0);
                break;
            }
            tail = &tt->next;
        }
        *tail = NULL;
    }

    if (label) {
        if (dont_prepend < 0)
            free_tlist(startline);
        else {
            ll = nasm_malloc(sizeof(Line));
            ll->finishes = NULL;
            ll->next = istk->expansion;
            istk->expansion = ll;
            ll->first = startline;
            if (!dont_prepend) {
                while (label->next)
                    label = label->next;
                label->next = tt = new_Token(NULL, TOK_OTHER, ":", 0);
            }
        }
    }

    lfmt->uplevel(m->nolist ? LIST_MACRO_NOLIST : LIST_MACRO);

    return 1;
}
}
