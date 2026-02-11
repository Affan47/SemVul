mono_ldtoken_wrapper_generic_shared (MonoImage *image, int token, MonoMethod *method)
{
	MonoMethodSignature *sig = mono_method_signature (method);
	MonoGenericContext *generic_context;

	if (sig->is_inflated) {
		generic_context = mono_method_get_context (method);
	} else {
		MonoGenericContainer *generic_container = mono_method_get_generic_container (method);
		g_assert (generic_container);
		generic_context = &generic_container->context;
	}

	return mono_ldtoken_wrapper (image, token, generic_context);
}
