window_bind_destroy(WINDOW_REC *window, WINDOW_BIND_REC *rec)
{
	g_return_if_fail(window != NULL);
        g_return_if_fail(rec != NULL);

	window->bound_items = g_slist_remove(window->bound_items, rec);

        g_free(rec->servertag);
        g_free(rec->name);
        g_free(rec);
}
