set_anon_gparam_class (MonoGenericParam *param, gboolean is_mvar, MonoClass *klass)
{
	int n = mono_generic_param_num (param) | ((guint32)param->serial << 16);
	MonoImage *image = param->image;
	GHashTable *ht;

	g_assert (image);

	if (n < FAST_CACHE_SIZE) {
		if (is_mvar) {

			if (!image->mvar_cache_fast)
				image->mvar_cache_fast = mono_image_alloc0 (image, sizeof (MonoClass*) * FAST_CACHE_SIZE);
			image->mvar_cache_fast [n] = klass;
		} else {
			if (!image->var_cache_fast)
				image->var_cache_fast = mono_image_alloc0 (image, sizeof (MonoClass*) * FAST_CACHE_SIZE);
			image->var_cache_fast [n] = klass;
		}
		return;
	}
	ht = is_mvar ? image->mvar_cache_slow : image->var_cache_slow;
	if (!ht) {
		mono_loader_lock ();
		ht = is_mvar ? image->mvar_cache_slow : image->var_cache_slow;
		if (!ht) {
			ht = g_hash_table_new (NULL, NULL);
			mono_memory_barrier ();
			if (is_mvar)
				image->mvar_cache_slow = ht;
			else
				image->var_cache_slow = ht;
		}
		mono_loader_unlock ();
	}

	g_hash_table_insert (ht, GINT_TO_POINTER (n), klass);
}
