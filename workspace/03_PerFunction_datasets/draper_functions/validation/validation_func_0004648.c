gc_alloc (MonoProfiler *prof, MonoObject *obj, MonoClass *klass)
{
	uint64_t now;
	uintptr_t len;
	int do_bt = (nocalls && runtime_inited && !notraces)? TYPE_ALLOC_BT: 0;
	FrameData data;
	LogBuffer *logbuffer;
	len = mono_object_get_size (obj);

	len += 7;
	len &= ~7;
	if (do_bt)
		collect_bt (&data);
	logbuffer = ensure_logbuf (32 + MAX_FRAMES * 8);
	now = current_time ();
	ENTER_LOG (logbuffer, "gcalloc");
	emit_byte (logbuffer, do_bt | TYPE_ALLOC);
	emit_time (logbuffer, now);
	emit_ptr (logbuffer, klass);
	emit_obj (logbuffer, obj);
	emit_value (logbuffer, len);
	if (do_bt)
		emit_bt (logbuffer, &data);
	EXIT_LOG (logbuffer);
	if (logbuffer->next)
		safe_dump (prof, logbuffer);
	process_requests (prof);

}
