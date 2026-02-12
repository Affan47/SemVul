static void expand_mmac_params_range(MMacro *mac, Token *tline, Token ***tail)
{
    Token *t;
    const char *arg = tok_text(tline) + 1;
    int fst, lst, incr, n;
    int parsed;

    parsed = sscanf(arg, "%d:%d", &fst, &lst);
    nasm_assert(parsed == 2);


    if (lst == 0 || fst == 0)
        goto err;


    if ((fst > (int)mac->nparam || fst < (-(int)mac->nparam)) ||
        (lst > (int)mac->nparam || lst < (-(int)mac->nparam)))
        goto err;

    fst = fst < 0 ? fst + (int)mac->nparam + 1: fst;
    lst = lst < 0 ? lst + (int)mac->nparam + 1: lst;


    incr = (fst < lst) ? 1 : -1;

    while (true) {
        n = mmac_rotate(mac, fst);
        dup_tlistn(mac->params[n], mac->paramlen[n], tail);
        if (fst == lst)
            break;
        t = make_tok_char(NULL, ',');
        **tail = t;
        *tail = &t->next;
        fst += incr;
    }

    return;

err:
    nasm_nonfatal("`%%{%s}': macro parameters out of range", arg);
    return;
}
