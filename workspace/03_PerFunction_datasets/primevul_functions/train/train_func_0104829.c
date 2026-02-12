static MMacro *is_mmacro(Token * tline, int *nparamp, Token ***paramsp)
{
    MMacro *head, *m, *found;
    Token **params, **comma;
    int raw_nparam, nparam;
    const char *finding = tok_text(tline);
    bool empty_args = !tline->next;

    *nparamp = 0;
    *paramsp = NULL;

    head = (MMacro *) hash_findix(&mmacros, finding);


    list_for_each(m, head) {
        if (!mstrcmp(m->name, finding, m->casesense) &&
            (m->in_progress != 1 || m->max_depth > 0))
            break;
    }
    if (!m)
        return NULL;


    comma = count_mmac_params(tline->next, nparamp, paramsp);
    raw_nparam = *nparamp;


    found = find_mmacro_in_list(m, finding, nparamp, paramsp);
    if (!*paramsp)
        return NULL;

    nparam = *nparamp;
    params = *paramsp;


    if (!ppopt.sane_empty_expansion) {
        if (!found) {
            if (raw_nparam == 0 && !empty_args) {


                int bogus_nparam = 1;
                params[2] = NULL;
                found = find_mmacro_in_list(m, finding, &bogus_nparam, paramsp);
            } else if (raw_nparam > 1 && comma) {
                Token *comma_tail = *comma;


                *comma = NULL;
                *nparamp = raw_nparam - 1;
                found = find_mmacro_in_list(m, finding, nparamp, paramsp);
                if (found)
                    free_tlist(comma_tail);
                else
                    *comma = comma_tail;
            }

            if (!*paramsp)
                return NULL;
        } else if (comma) {
            free_tlist(*comma);
            *comma = NULL;
            if (raw_nparam > found->nparam_min &&
                raw_nparam <= found->nparam_min + found->ndefs) {

                params[raw_nparam] =
                    found->defaults[raw_nparam - found->nparam_min];
            } else if (raw_nparam > found->nparam_max && found->plus) {

            } else {

                params[raw_nparam] = NULL;
                *nparamp = nparam = raw_nparam - 1;
            }
        }

        if (found) {
            if (raw_nparam < found->nparam_min ||
                (raw_nparam > found->nparam_max && !found->plus)) {
                nasm_warn(WARN_MACRO_PARAMS_LEGACY,
                          "improperly calling multi-line macro `%s' with %d parameters",
                          found->name, raw_nparam);
            } else if (comma) {
                nasm_warn(WARN_MACRO_PARAMS_LEGACY,
                          "dropping trailing empty parameter in call to multi-line macro `%s'", found->name);
            }
        }
    }


    if (found)
        return found;

    nasm_warn(WARN_MACRO_PARAMS_MULTI,
               "multi-line macro `%s' exists, but not taking %d parameter%s",
              finding, nparam, (nparam == 1) ? "" : "s");
    nasm_free(*paramsp);
    return NULL;
}
