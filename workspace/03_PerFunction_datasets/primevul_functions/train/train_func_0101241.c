mono_method_is_valid_generic_instantiation (VerifyContext *ctx, MonoMethod *method)
{
	MonoMethodInflated *gmethod = (MonoMethodInflated *)method;
	MonoGenericInst *ginst = gmethod->context.method_inst;
	MonoGenericContainer *gc = mono_method_get_generic_container (gmethod->declaring);
	if (!gc)
		return TRUE;
	if (ctx && !is_valid_generic_instantiation_in_context (ctx, ginst))
		return FALSE;
	return is_valid_generic_instantiation (gc, &gmethod->context, ginst);

}
