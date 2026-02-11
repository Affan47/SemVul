mono_image_get_public_key (MonoImage *image, guint32 *size)
{
	const char *pubkey;
	guint32 len, tok;

	if (image->dynamic) {
		if (size)
			*size = ((MonoDynamicImage*)image)->public_key_len;
		return (char*)((MonoDynamicImage*)image)->public_key;
	}
	if (image->tables [MONO_TABLE_ASSEMBLY].rows != 1)
		return NULL;
	tok = mono_metadata_decode_row_col (&image->tables [MONO_TABLE_ASSEMBLY], 0, MONO_ASSEMBLY_PUBLIC_KEY);
	if (!tok)
		return NULL;
	pubkey = mono_metadata_blob_heap (image, tok);
	len = mono_metadata_decode_blob_size (pubkey, &pubkey);
	if (size)
		*size = len;
	return pubkey;
}
