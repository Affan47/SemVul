clear_cached_culture (gpointer key, gpointer value, gpointer user_data)
{
	MonoInternalThread *thread = (MonoInternalThread*)value;
	MonoDomain *domain = (MonoDomain*)user_data;
	int i;


	if (thread->cached_culture_info) {
		for (i = 0; i < NUM_CACHED_CULTURES * 2; ++i) {
			MonoObject *obj = mono_array_get (thread->cached_culture_info, MonoObject*, i);
			if (obj && obj->vtable->domain == domain)
				mono_array_set (thread->cached_culture_info, MonoObject*, i, NULL);
		}
	}
}
