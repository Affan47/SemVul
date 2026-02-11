version(void)
{
    void            (*func)(void);
    char            *name;

    trace(("version()\n{\n"));
    arglex();
    name = 0;
    while (arglex_token != arglex_token_eoln)
    {
        switch (arglex_token)
        {
        default:
            generic_argument(usage);
            continue;

        case arglex_token_string:
            if (name)
                fatal_raw("too many info names");
            name = arglex_value.alv_string;
            break;
        }
        arglex();
    }

    if (name)
    {
        int             nhit;
        table_ty       *tp;
        string_ty      *s1;
        string_ty      *s2;
        table_ty       *hit[SIZEOF(table)];
        int             j;

        nhit = 0;
        for (tp = table; tp < ENDOF(table); ++tp)
        {
            if (arglex_compare(tp->name, name))
                hit[nhit++] = tp;
        }
        switch (nhit)
        {
        case 0:
            fatal_raw("no info %s", name);

        case 1:
            break;

        default:
            s1 = str_from_c(hit[0]->name);
            for (j = 1; j < nhit; ++j)
            {
                s2 = str_format("%s, %s", s1->str_text, hit[j]->name);
                str_free(s1);
                s1 = s2;
            }
            fatal_raw("info %s ambig (%s)", name, s1->str_text);
        }
        arglex();
        func = hit[0]->func;
    }
    else
        func = version_copyright;

    func();
    trace(("}\n"));
}
