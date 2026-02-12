static void pp_add_stdmac(macros_t *macros)
{
    macros_t **mp;


    for (mp = stdmacros; *mp; mp++) {
        if (*mp == macros)
            return;
    }

    nasm_assert(mp < &stdmacros[ARRAY_SIZE(stdmacros)-1]);

    *mp = macros;
}
