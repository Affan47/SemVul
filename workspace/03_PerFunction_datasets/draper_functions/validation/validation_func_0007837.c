popstring(void)
{
	struct strpush *sp = g_parsefile->strpush;

	INT_OFF;
#if ENABLE_ASH_ALIAS
	if (sp->ap) {
		if (g_parsefile->next_to_pgetc[-1] == ' '
		 || g_parsefile->next_to_pgetc[-1] == '\t'
		) {
			checkkwd |= CHKALIAS;
		}
		if (sp->string != sp->ap->val) {
			free(sp->string);
		}
		sp->ap->flag &= ~ALIASINUSE;
		if (sp->ap->flag & ALIASDEAD) {
			unalias(sp->ap->name);
		}
	}
#endif
	g_parsefile->next_to_pgetc = sp->prev_string;
	g_parsefile->left_in_line = sp->prev_left_in_line;
	g_parsefile->strpush = sp->prev;
	if (sp != &(g_parsefile->basestrpush))
		free(sp);
	INT_ON;
}
