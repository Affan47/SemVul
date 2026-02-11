altstack_handle_and_restore (MonoContext *ctx, MonoObject *obj, gboolean stack_ovf)
{
	MonoContext mctx;

	mctx = *ctx;

	mono_handle_exception (&mctx, obj);
	if (stack_ovf)
		prepare_for_guard_pages (&mctx);
	mono_restore_context (&mctx);
}
