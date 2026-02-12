static void pp_list_one_macro(MMacro *m, int severity)
{
    if (!m)
	return;


    pp_list_one_macro(m->next_active, severity);

    if (m->name && !m->nolist) {
	src_set(m->xline + m->lineno, m->fname);
	nasm_error(severity, "... from macro `%s' defined here", m->name);
    }
}
