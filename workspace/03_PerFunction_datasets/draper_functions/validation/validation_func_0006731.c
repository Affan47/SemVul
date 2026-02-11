inflated_signature_equal (gconstpointer a, gconstpointer b)
{
	const MonoInflatedMethodSignature *sig1 = (const MonoInflatedMethodSignature *)a;
	const MonoInflatedMethodSignature *sig2 = (const MonoInflatedMethodSignature *)b;


	if (sig1->sig != sig2->sig)
		return FALSE;

	return mono_metadata_generic_context_equal (&sig1->context, &sig2->context);
}
