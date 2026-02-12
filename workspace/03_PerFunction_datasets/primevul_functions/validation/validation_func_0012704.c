static SMacro *expand_one_smacro(Token ***tpp)
{
    Token **params = NULL;
    const char *mname;
    Token *mstart = **tpp;
    Token *tline  = mstart;
    SMacro *head, *m;
    int i;
    Token *t, *tup, *tafter;
    int nparam = 0;
    bool cond_comma;

    if (!tline)
        return false;

    mname = tok_text(mstart);

    smacro_deadman.total--;
    smacro_deadman.levels--;

    if (unlikely(smacro_deadman.total < 0 || smacro_deadman.levels < 0)) {
        if (unlikely(!smacro_deadman.triggered)) {
            nasm_nonfatal("interminable macro recursion");
            smacro_deadman.triggered = true;
        }
        goto not_a_macro;
    } else if (tline->type == TOK_ID || tline->type == TOK_PREPROC_ID) {
        head = (SMacro *)hash_findix(&smacros, mname);
    } else if (tline->type == TOK_LOCAL_MACRO) {
        Context *ctx = get_ctx(mname, &mname);
        head = ctx ? (SMacro *)hash_findix(&ctx->localmac, mname) : NULL;
    } else {
        goto not_a_macro;
    }


    list_for_each(m, head) {
        if (unlikely(m->alias && ppopt.noaliases))
            continue;
        if (!mstrcmp(m->name, mname, m->casesense))
            break;
    }

    if (!m) {
        goto not_a_macro;
    }


    params = NULL;
    nparam = 0;

    if (m->nparam == 0) {


    } else {


        Token *t;
        int paren, brackets;

        tline = tline->next;
        tline = skip_white(tline);
        if (!tok_is(tline, '(')) {


            goto not_a_macro;
        }

        paren = 1;
        nparam = 1;
        brackets = 0;
        t = tline;

        while (paren) {
            t = t->next;

            if (!t) {
                nasm_nonfatal("macro call expects terminating `)'");
                goto not_a_macro;
            }

            if (t->type != TOK_OTHER || t->len != 1)
                continue;

            switch (t->text.a[0]) {
            case ',':
                if (!brackets && paren == 1)
                    nparam++;
                break;

            case '{':
                brackets++;
                break;

            case '}':
                if (brackets > 0)
                    brackets--;
                break;

            case '(':
                if (!brackets)
                    paren++;
                break;

            case ')':
                if (!brackets)
                    paren--;
                break;

            default:
                break;
            }
        }


        while (1) {
            if (!m) {


                nasm_warn(WARN_MACRO_PARAMS_SINGLE|ERR_HOLD,
                    "single-line macro `%s' exists, "
                    "but not taking %d parameter%s",
                    mname, nparam, (nparam == 1) ? "" : "s");
                goto not_a_macro;
            }

            if (!mstrcmp(m->name, mname, m->casesense)) {
                if (nparam == m->nparam)
                    break;
                if (m->greedy && nparam >= m->nparam-1)
                    break;
            }
            m = m->next;
        }
    }

    if (m->in_progress)
        goto not_a_macro;


    m->in_progress = true;

    if (nparam) {

        Token **phead, **pep;
        int white = 0;
        int brackets = 0;
        int paren;
        bool bracketed = false;
        bool bad_bracket = false;
        enum sparmflags flags;

        nparam = m->nparam;
        paren = 1;
        nasm_newn(params, nparam);
        i = 0;
        flags = m->params[i].flags;
        phead = pep = &params[i];
        *pep = NULL;

        while (paren) {
            bool skip;
            char ch;

            tline = tline->next;

            if (!tline)
                nasm_nonfatal("macro call expects terminating `)'");

            ch = 0;
            skip = false;


            switch (tline->type) {
            case TOK_OTHER:
                if (tline->len == 1)
                    ch = tline->text.a[0];
                break;

            case TOK_WHITESPACE:
                if (!(flags & SPARM_NOSTRIP)) {
                    if (brackets || *phead)
                        white++;
                    skip = true;
                }
                break;

            default:
                break;
            }

            switch (ch) {
            case ',':
                if (!brackets && paren == 1 && !(flags & SPARM_GREEDY)) {
                    i++;
                    nasm_assert(i < nparam);
                    phead = pep = &params[i];
                    *pep = NULL;
                    bracketed = false;
                    skip = true;
                    flags = m->params[i].flags;
                }
                break;

            case '{':
                if (!bracketed) {
                    bracketed = !*phead && !(flags & SPARM_NOSTRIP);
                    skip = bracketed;
                }
                brackets++;
                break;

            case '}':
                if (brackets > 0) {
                    if (!--brackets)
                        skip = bracketed;
                }
                break;

            case '(':
                if (!brackets)
                    paren++;
                break;

            case ')':
                if (!brackets) {
                    paren--;
                    if (!paren) {
                        skip = true;
                        i++;
                    }
                }
                break;

            default:
                break;
            }

            if (!skip) {
                Token *t;

                bad_bracket |= bracketed && !brackets;

                if (white) {
                    *pep = t = new_White(NULL);
                    pep = &t->next;
                    white = 0;
                }
                *pep = t = dup_Token(NULL, tline);
                pep = &t->next;
            }
        }


        for (i = 0; i < nparam; i++) {
            enum sparmflags flags = m->params[i].flags;

            if (flags & SPARM_EVAL) {

                struct ppscan pps;
                struct tokenval tokval;
                expr *evalresult;
                Token *eval_param;

                pps.tptr = eval_param = expand_smacro_noreset(params[i]);
                pps.ntokens = -1;
                tokval.t_type = TOKEN_INVALID;
                evalresult = evaluate(ppscan, &pps, &tokval, NULL, true, NULL);

                free_tlist(eval_param);
                params[i] = NULL;

                if (!evalresult) {

                } else if (tokval.t_type) {
                    nasm_nonfatal("invalid expression in parameter %d of macro `%s'", i, m->name);
                } else if (!is_simple(evalresult)) {
                    nasm_nonfatal("non-constant expression in parameter %d of macro `%s'", i, m->name);
                } else {
                    params[i] = make_tok_num(NULL, reloc_value(evalresult));
                }
            }

            if (flags & SPARM_STR) {

                char *arg;
                Token *qs;

                qs = expand_smacro_noreset(params[i]);
                arg = detoken(qs, false);
                free_tlist(qs);
                params[i] = make_tok_qstr(NULL, arg);
                nasm_free(arg);
            }
        }
    }


    t = m->expand(m, params, nparam);

    tafter = tline->next;
    tline->next = NULL;
    tline = tafter;

    tup = NULL;
    cond_comma = false;

    while (t) {
        enum pp_token_type type = t->type;
        Token *tnext = t->next;

        switch (type) {
        case TOK_PREPROC_Q:
        case TOK_PREPROC_SQ:
            delete_Token(t);
            t = dup_Token(tline, mstart);
            break;

        case TOK_PREPROC_QQ:
        case TOK_PREPROC_SQQ:
        {
            size_t mlen = strlen(m->name);
	    size_t len;
            char *p, *from;

            t->type = mstart->type;
            if (t->type == TOK_LOCAL_MACRO) {
		const char *psp;
                const char *pep;
		size_t plen;

		psp = tok_text(mstart);
                get_ctx(psp, &pep);
                plen = pep - psp;

                len = mlen + plen;
                from = p = nasm_malloc(len + 1);
                p = mempcpy(p, psp, plen);
            } else {
                len = mlen;
                from = p = nasm_malloc(len + 1);
            }
            p = mempcpy(p, m->name, mlen);
            *p = '\0';
	    set_text_free(t, from, len);

            t->next = tline;
            break;
        }

        case TOK_COND_COMMA:
            delete_Token(t);
            t = cond_comma ? make_tok_char(tline, ',') : NULL;
            break;

        case TOK_ID:
        case TOK_PREPROC_ID:
	case TOK_LOCAL_MACRO:
        {


            Token **tp = &t;
            t->next = tline;
            expand_one_smacro(&tp);
            tline = *tp;
            break;
        }
        default:
            if (is_smac_param(t->type)) {
                int param = smac_nparam(t->type);
                nasm_assert(!tup && param < nparam);
                delete_Token(t);
                t = NULL;
                tup = tnext;
                tnext = dup_tlist_reverse(params[param], NULL);
                cond_comma = false;
            } else {
                t->next = tline;
            }
        }

        if (t) {
            Token *endt = tline;

            tline = t;
            while (!cond_comma && t && t != endt) {
                cond_comma = t->type != TOK_WHITESPACE;
                t = t->next;
            }
        }

        if (tnext) {
            t = tnext;
        } else {
            t = tup;
            tup = NULL;
        }
    }

    **tpp = tline;
    for (t = tline; t && t != tafter; t = t->next)
        *tpp = &t->next;

    m->in_progress = false;


    free_tlist(mstart);
    goto done;


not_a_macro:
    *tpp = &mstart->next;
    m = NULL;
done:
    smacro_deadman.levels++;
    if (unlikely(params))
        free_tlist_array(params, nparam);
    return m;
}
