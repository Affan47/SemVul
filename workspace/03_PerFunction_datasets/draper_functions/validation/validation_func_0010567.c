probe_remove_event_call(struct trace_event_call *call)
{
	struct trace_array *tr;
	struct trace_event_file *file;

#ifdef CONFIG_PERF_EVENTS
	if (call->perf_refcount)
		return -EBUSY;
#endif
	do_for_each_event_file(tr, file) {
		if (file->event_call != call)
			continue;


		if (file->flags & EVENT_FILE_FL_ENABLED)
			return -EBUSY;


		break;
	} while_for_each_event_file();

	__trace_remove_event_call(call);

	return 0;
}
