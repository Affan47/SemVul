mono_image_loaded_full (const char *name, gboolean refonly)
{
	MonoImage *res;
	GHashTable *loaded_images = refonly ? loaded_images_refonly_hash : loaded_images_hash;

	mono_images_lock ();
	res = g_hash_table_lookup (loaded_images, name);
	mono_images_unlock ();
	return res;
}
