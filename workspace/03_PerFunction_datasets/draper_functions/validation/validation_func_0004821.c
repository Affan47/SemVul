setup_jit_tls_data (gpointer stack_start, gpointer abort_func)
{
	MonoJitTlsData *jit_tls;
	MonoLMF *lmf;

	jit_tls = mono_native_tls_get_value (mono_jit_tls_id);
	if (jit_tls)
		return jit_tls;

	jit_tls = g_new0 (MonoJitTlsData, 1);

	jit_tls->abort_func = abort_func;
	jit_tls->end_of_stack = stack_start;

	mono_set_jit_tls (jit_tls);

	lmf = g_new0 (MonoLMF, 1);
	MONO_ARCH_INIT_TOP_LMF_ENTRY (lmf);

	jit_tls->first_lmf = lmf;

#if defined(MONO_HAVE_FAST_TLS) && defined(MONO_ARCH_ENABLE_MONO_LMF_VAR)

	MONO_FAST_TLS_SET (mono_lmf, lmf);
	mono_set_lmf_addr (MONO_FAST_TLS_ADDR (mono_lmf));
#else
	mono_set_lmf_addr (&jit_tls->lmf);

	jit_tls->lmf = lmf;
#endif

#ifdef MONO_ARCH_HAVE_TLS_INIT
	mono_arch_tls_init ();
#endif

	mono_setup_altstack (jit_tls);

	return jit_tls;
}
