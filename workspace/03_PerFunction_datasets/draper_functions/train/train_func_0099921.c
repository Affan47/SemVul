mono_create_jump_trampoline (MonoDomain *domain, MonoMethod *method, gboolean add_sync_wrapper)
{
	MonoJitInfo *ji;
	gpointer code;
	guint32 code_size = 0;

	code = mono_jit_find_compiled_method_with_jit_info (domain, method, &ji);


	if (code && !ji->has_generic_jit_info && !(method->iflags & METHOD_IMPL_ATTRIBUTE_SYNCHRONIZED))
		return code;

	if (mono_llvm_only)
		return mono_jit_compile_method (method);

	mono_domain_lock (domain);
	code = g_hash_table_lookup (domain_jit_info (domain)->jump_trampoline_hash, method);
	mono_domain_unlock (domain);
	if (code)
		return code;

	code = mono_create_specific_trampoline (method, MONO_TRAMPOLINE_JUMP, mono_domain_get (), &code_size);
	g_assert (code_size);

	ji = (MonoJitInfo *)mono_domain_alloc0 (domain, MONO_SIZEOF_JIT_INFO);
	ji->code_start = code;
	ji->code_size = code_size;
	ji->d.method = method;


	mono_jit_info_table_add (domain, ji);

	mono_domain_lock (domain);
	g_hash_table_insert (domain_jit_info (domain)->jump_trampoline_hash, method, ji->code_start);
	mono_domain_unlock (domain);

	return ji->code_start;
}
