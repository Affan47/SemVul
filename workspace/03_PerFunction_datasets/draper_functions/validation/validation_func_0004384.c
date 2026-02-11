push_parser (gpointer data)
{
	guint i;
	TotemPlParser *pl = TOTEM_PL_PARSER (data);

	for (i = 0; uris[i] != NULL; ++i)
		test_parsing_real (pl, uris[i]);

	g_main_loop_quit (loop);

	return FALSE;
}
