int apply_event_filter(struct trace_event_file *file, char *filter_string)
{
	struct trace_event_call *call = file->event_call;
	struct event_filter *filter = NULL;
	int err;

	if (!strcmp(strstrip(filter_string), "0")) {
		filter_disable(file);
		filter = event_filter(file);

		if (!filter)
			return 0;

		event_clear_filter(file);


		tracepoint_synchronize_unregister();
		__free_filter(filter);

		return 0;
	}

	err = create_filter(file->tr, call, filter_string, true, &filter);


	if (filter) {
		struct event_filter *tmp;

		tmp = event_filter(file);
		if (!err)
			event_set_filtered_flag(file);
		else
			filter_disable(file);

		event_set_filter(file, filter);

		if (tmp) {

			tracepoint_synchronize_unregister();
			__free_filter(tmp);
		}
	}

	return err;
}
