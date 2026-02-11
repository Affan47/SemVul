create(const nstring &name)
{
    if (name.empty())
        return new target_makefile();
    const table_t *best = 0;
    double best_weight = 0.6;
    for (const table_t *tp = table; tp < ENDOF(table); ++tp)
    {
        if (name == tp->name)
            return tp->func();
        double w = fstrcmp(name.c_str(), tp->name);
        if (best_weight < w)
        {
            best_weight = w;
            best = tp;
        }
    }
    if (best)
    {
        sub_context_ty sc;
        sc.var_set_string("name", name);
        sc.var_set_string("guess", best->name);
        sc.fatal_intl(i18n("no \"$name\", guessing \"$guess\""));
    }
    else
    {
        sub_context_ty sc;
        sc.var_set_string("Name", name);
        sc.fatal_intl(i18n("the name \"$name\" is undefined"));
    }
    return 0;
}
