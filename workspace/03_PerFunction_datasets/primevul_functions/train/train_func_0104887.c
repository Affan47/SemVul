find_mmacro_in_list(MMacro *m, const char *finding,
                    int *nparamp, Token ***paramsp)
{
    int nparam = *nparamp;

    while (m) {
        if (m->nparam_min <= nparam
            && (m->plus || nparam <= m->nparam_max)) {


            return use_mmacro(m, nparamp, paramsp);
        }


        list_for_each(m, m->next) {
            if (!mstrcmp(m->name, finding, m->casesense))
                break;
        }
    }

    return NULL;
}
