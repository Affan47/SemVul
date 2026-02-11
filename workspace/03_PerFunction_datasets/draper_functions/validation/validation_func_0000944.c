continuation_restore (MonoContinuation *cont, int state)
{
	MonoLMF **lmf_addr = mono_get_lmf_addr ();
	MonoContinuationRestore restore_state = mono_tasklets_arch_restore ();

	if (!cont->domain || !cont->return_sp)
		return mono_get_exception_argument ("cont", "Continuation not initialized");
	if (cont->domain != mono_domain_get () || !mono_native_thread_id_equals (cont->thread_id, mono_native_thread_id_get ()))
		return mono_get_exception_argument ("cont", "Continuation from another thread or domain");


	*lmf_addr = cont->lmf;
	restore_state (cont, state, lmf_addr);
	g_assert_not_reached ();
}
