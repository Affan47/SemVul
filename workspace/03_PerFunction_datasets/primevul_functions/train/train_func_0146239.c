ves_icall_MonoMethod_GetGenericMethodDefinition (MonoReflectionMethod *method)
{
	MonoMethodInflated *imethod;
	MonoMethod *result;

	MONO_ARCH_SAVE_REGS;

	if (method->method->is_generic)
		return method;

	if (!method->method->is_inflated)
		return NULL;

	imethod = (MonoMethodInflated *) method->method;

	result = imethod->declaring;

	if (!result->is_generic)
		return NULL;

	if (method->method->klass->image->dynamic) {
		MonoDynamicImage *image = (MonoDynamicImage*)method->method->klass->image;
		MonoReflectionMethod *res;


		mono_loader_lock ();
		res = mono_g_hash_table_lookup (image->generic_def_objects, imethod);
		mono_loader_unlock ();

		if (res)
			return res;
	}

	if (imethod->context.class_inst) {
		MonoClass *klass = ((MonoMethod *) imethod)->klass;

		if (mono_class_get_context (klass))
			result = mono_class_inflate_generic_method_full (result, klass, mono_class_get_context (klass));
	}

	return mono_method_get_object (mono_object_domain (method), result, NULL);
}
