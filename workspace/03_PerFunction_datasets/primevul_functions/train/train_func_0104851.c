static MMacro *use_mmacro(MMacro *m, int *nparamp, Token ***paramsp)
{
    int nparam = *nparamp;
    Token **params = *paramsp;


    if (m->in_progress > m->max_depth) {
        if (m->max_depth > 0) {
            nasm_warn(WARN_OTHER, "reached maximum recursion depth of %i",
                      m->max_depth);
        }
        nasm_free(params);
        *nparamp = 0;
        *paramsp = NULL;
        return NULL;
    }


    if (m->defaults && nparam < m->nparam_min + m->ndefs) {
        int newnparam = m->nparam_min + m->ndefs;
        params = nasm_realloc(params, sizeof(*params) * (newnparam+2));
        memcpy(&params[nparam+1], &m->defaults[nparam+1-m->nparam_min],
               (newnparam - nparam) * sizeof(*params));
        nparam = newnparam;
    }


    if (m->plus && nparam > m->nparam_max)
        nparam = m->nparam_max;


    params[nparam+1] = NULL;


    *paramsp = params;
    *nparamp = nparam;
    return m;
}
