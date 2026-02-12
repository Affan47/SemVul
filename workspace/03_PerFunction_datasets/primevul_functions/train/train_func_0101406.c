static MMacro *is_mmacro(Token * tline, Token *** params_array)
{
    MMacro *head, *m;
    Token **params;
    int nparam;

    head = (MMacro *) hash_findix(&mmacros, tline->text);


    list_for_each(m, head)
        if (!mstrcmp(m->name, tline->text, m->casesense))
            break;
    if (!m)
        return NULL;


    count_mmac_params(tline->next, &nparam, &params);


    while (m) {
        if (m->nparam_min <= nparam
            && (m->plus || nparam <= m->nparam_max)) {


            if (m->in_progress > m->max_depth) {
                if (m->max_depth > 0) {
                    nasm_error(ERR_WARNING,
                          "reached maximum recursion depth of %i",
                          m->max_depth);
                }
                nasm_free(params);
                return NULL;
            }


            if (m->defaults && nparam < m->nparam_min + m->ndefs) {
                params =
                    nasm_realloc(params,
                                 ((m->nparam_min + m->ndefs +
                                   1) * sizeof(*params)));
                while (nparam < m->nparam_min + m->ndefs) {
                    params[nparam] = m->defaults[nparam - m->nparam_min];
                    nparam++;
                }
            }


            if (m->plus && nparam > m->nparam_max)
                nparam = m->nparam_max;


            if (!params) {
                params = nasm_malloc(sizeof(*params));
                nparam = 0;
            }
            params[nparam] = NULL;
            *params_array = params;
            return m;
        }


        list_for_each(m, m->next)
            if (!mstrcmp(m->name, tline->text, m->casesense))
                break;
    }


    nasm_error(ERR_WARNING|ERR_PASS1|ERR_WARN_MNP,
          "macro `%s' exists, but not taking %d parameters",
          tline->text, nparam);
    nasm_free(params);
    return NULL;
}
