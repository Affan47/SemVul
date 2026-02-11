tm_symbol_print(TMSymbol *sym, guint level)
{
	guint i;

	g_return_if_fail (sym != NULL);
	for (i=0; i < level; ++i)
		fputc('\t', stderr);
	fprintf(stderr, "%s\n", (sym->tag)?sym->tag->name:"Root");
	if (sym->info.children)
	{
		if (sym->tag && tm_tag_function_t == sym->tag->type)
			tm_tag_print(sym->info.equiv, stderr);
		else
		{
			for (i=0; i < sym->info.children->len; ++i)
				tm_symbol_print(TM_SYMBOL(sym->info.children->pdata[i])
				  , level + 1);
		}
	}
}
