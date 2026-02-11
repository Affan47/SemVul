get_provenance (StackFrameInfo *frame, MonoContext *ctx, gpointer data)
{
	MonoJitInfo *ji = frame->ji;
	MonoMethod *method;
	if (!ji)
		return FALSE;
	method = jinfo_get_method (ji);
	if (method->wrapper_type != MONO_WRAPPER_NONE)
		return FALSE;
	*(gpointer *)data = method;
	return TRUE;
}
