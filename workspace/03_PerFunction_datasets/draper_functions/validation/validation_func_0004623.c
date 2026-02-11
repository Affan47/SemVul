sc_speller_dict_suggest(const gchar *word, gsize *n_suggs)
{
	g_return_val_if_fail(sc_speller_dict != NULL, NULL);
	g_return_val_if_fail(word != NULL, NULL);

	return enchant_dict_suggest(sc_speller_dict, word, -1, n_suggs);
}
