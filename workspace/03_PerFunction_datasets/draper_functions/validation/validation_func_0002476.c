update_current_thread_stack (void *start)
{
	int stack_guard = 0;
#if !defined(USE_MONO_CTX)
	void *reg_ptr = cur_thread_regs;
#endif
	SgenThreadInfo *info = mono_thread_info_current ();

	info->client_info.stack_start = align_pointer (&stack_guard);
	g_assert (info->client_info.stack_start >= info->client_info.stack_start_limit && info->client_info.stack_start < info->client_info.stack_end);
#ifdef USE_MONO_CTX
	MONO_CONTEXT_GET_CURRENT (cur_thread_ctx);
	memcpy (&info->client_info.ctx, &cur_thread_ctx, sizeof (MonoContext));
	if (mono_gc_get_gc_callbacks ()->thread_suspend_func)
		mono_gc_get_gc_callbacks ()->thread_suspend_func (info->client_info.runtime_data, NULL, &info->client_info.ctx);
#else
	ARCH_STORE_REGS (reg_ptr);
	memcpy (&info->client_info.regs, reg_ptr, sizeof (info->client_info.regs));
	if (mono_gc_get_gc_callbacks ()->thread_suspend_func)
		mono_gc_get_gc_callbacks ()->thread_suspend_func (info->client_info.runtime_data, NULL, NULL);
#endif
}
