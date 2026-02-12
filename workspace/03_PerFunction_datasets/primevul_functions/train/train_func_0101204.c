mono_reflection_cleanup_domain (MonoDomain *domain)
{
	if (domain->refobject_hash) {

#ifdef REFENTRY_REQUIRES_CLEANUP
		mono_g_hash_table_foreach (domain->refobject_hash, cleanup_refobject_hash, NULL);
#endif
		mono_g_hash_table_destroy (domain->refobject_hash);
		domain->refobject_hash = NULL;
	}
}
