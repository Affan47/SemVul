print_stack_frame_to_stderr (StackFrameInfo *frame, MonoContext *ctx, gpointer data)
{
	MonoMethod *method = NULL;

	if (frame->ji && frame->type != FRAME_TYPE_TRAMPOLINE)
		method = jinfo_get_method (frame->ji);

	if (method) {
		gchar *location = mono_debug_print_stack_frame (method, frame->native_offset, mono_domain_get ());
		mono_runtime_printf_err ("  %s", location);
		g_free (location);
	} else
		mono_runtime_printf_err ("  at <unknown> <0x%05x>", frame->native_offset);

	return FALSE;
}
