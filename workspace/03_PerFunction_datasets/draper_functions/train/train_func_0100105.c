hilight_remove(HILIGHT_REC *rec)
{
	g_return_if_fail(rec != NULL);

	hilight_remove_config(rec);
	hilights = g_slist_remove(hilights, rec);

	signal_emit("hilight destroyed", 1, rec);
	hilight_destroy(rec);
}
