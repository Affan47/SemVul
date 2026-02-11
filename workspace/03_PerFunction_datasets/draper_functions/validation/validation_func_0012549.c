advsearch_set(AdvancedSearch *search, AdvancedSearchType type, const gchar *matchstring)
{
	cm_return_if_fail(search != NULL);

	search->request.type = type;

	g_free(search->request.matchstring);
	search->request.matchstring = g_strdup(matchstring);

	prepare_matcher(search);
}
