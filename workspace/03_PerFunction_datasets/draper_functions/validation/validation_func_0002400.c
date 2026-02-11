domain_name (MonoProfiler *prof, MonoDomain *domain, const char *name)
{
	int nlen = strlen (name) + 1;
	LogBuffer *logbuffer = ensure_logbuf (
		EVENT_SIZE  +
		LEB128_SIZE  +
		EVENT_SIZE  +
		LEB128_SIZE  +
		LEB128_SIZE  +
		nlen
	);
	uint64_t now = current_time ();

	ENTER_LOG (logbuffer, "domain-name");
	emit_byte (logbuffer, TYPE_METADATA);
	emit_time (logbuffer, now);
	emit_byte (logbuffer, TYPE_DOMAIN);
	emit_ptr (logbuffer, (void*)(uintptr_t) mono_domain_get_id (domain));
	emit_value (logbuffer, 0);
	memcpy (logbuffer->data, name, nlen);
	logbuffer->data += nlen;
	EXIT_LOG (logbuffer);

	if (logbuffer->next)
		safe_send (prof, logbuffer);

	process_requests (prof);
}
