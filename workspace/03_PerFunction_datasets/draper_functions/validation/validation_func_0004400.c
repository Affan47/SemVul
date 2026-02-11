textbuffer_view_insert_line(TEXT_BUFFER_VIEW_REC *view, LINE_REC *line)
{
        GSList *tmp;
	unsigned char update_counter;

	g_return_if_fail(view != NULL);
	g_return_if_fail(line != NULL);

	if (!view->buffer->last_eol)
                return;

        update_counter = view->cache->update_counter+1;
	view_update_cache(view, line, update_counter);
        view_insert_line(view, line);

	for (tmp = view->siblings; tmp != NULL; tmp = tmp->next) {
		TEXT_BUFFER_VIEW_REC *rec = tmp->data;

                view_update_cache(rec, line, update_counter);
		view_insert_line(rec, line);
	}
}
