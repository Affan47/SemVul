jk_map_get_string_list(jk_map_t *m,
                              const char *name,
                              unsigned int *list_len, const char *def)
{
    const char *l = jk_map_get_string(m, name, def);
    char **ar = NULL;

#ifdef _MT_CODE_PTHREAD
    char *lasts;
#endif

    *list_len = 0;

    if (l) {
        unsigned capacity = 0;
        unsigned idex = 0;
        char *p;
        char *v = jk_pool_strdup(&m->p, l);

        if (!v) {
            return NULL;
        }


#ifdef _MT_CODE_PTHREAD
        for (p = strtok_r(v, " \t,", &lasts);
             p; p = strtok_r(NULL, " \t,", &lasts))
#else
        for (p = strtok(v, " \t,"); p; p = strtok(NULL, " \t,"))
#endif

        {

            if (idex == capacity) {
                ar = jk_pool_realloc(&m->p,
                                     sizeof(char *) * (capacity + 5),
                                     ar, sizeof(char *) * capacity);
                if (!ar) {
                    return JK_FALSE;
                }
                capacity += 5;
            }
            ar[idex] = jk_pool_strdup(&m->p, p);
            idex++;
        }

        *list_len = idex;
    }

    return ar;
}
