assembly_binding_end (gpointer user_data, const char *element_name)
{
	ParserUserData *pud = user_data;

	if (!strcmp (element_name, "dependentAssembly")) {
		if (pud->info_parsed && pud->info) {
			pud->info_parsed (pud->info, pud->user_data);
			g_free (pud->info->name);
			g_free (pud->info->culture);
		}
	}
}
