static Token **count_mmac_params(Token *tline, int *nparamp, Token ***paramsp)
{
    int paramsize;
    int nparam = 0;
    Token *t;
    Token **comma = NULL, **maybe_comma = NULL;
    Token **params;

    paramsize = PARAM_DELTA;
    nasm_newn(params, paramsize);

    t = skip_white(tline);
    if (t) {
        while (true) {

            if (unlikely(nparam+2 >= paramsize)) {
                paramsize += PARAM_DELTA;
                params = nasm_realloc(params, sizeof(*params) * paramsize);
            }
            params[++nparam] = t;
            if (tok_is(t, '{')) {
                int brace = 1;

                comma = NULL;

                while (brace && (t = t->next)) {
                    brace += tok_is(t, '{');
                    brace -= tok_is(t, '}');
                }

                if (t) {

                    t = skip_white(t->next);
                    if (tok_isnt(t, ','))
                        nasm_nonfatal("braces do not enclose all of macro parameter");
                } else {
                    nasm_nonfatal("expecting closing brace in macro parameter");
                }
            }

            maybe_comma = &t->next;
            while (tok_isnt(t, ',')) {
                if (!tok_white(t))
                    comma = NULL;
                maybe_comma = &t->next;
                t = t->next;
            }

            if (!t)
                break;

            comma = maybe_comma;
            t = skip_white(t->next);
        }
    }

    params[nparam+1] = NULL;
    *paramsp = params;
    *nparamp = nparam;

    return comma;
}
}
