mono_metadata_interfaces_from_typedef_full (MonoImage *meta, guint32 index, MonoClass ***interfaces, guint *count, gboolean heap_alloc_result, MonoGenericContext *context, MonoError *error)
{
	MonoTableInfo *tdef = &meta->tables [MONO_TABLE_INTERFACEIMPL];
	locator_t loc;
	guint32 start, pos;
	guint32 cols [MONO_INTERFACEIMPL_SIZE];
	MonoClass **result;

	*interfaces = NULL;
	*count = 0;

	mono_error_init (error);

	if (!tdef->base)
		return TRUE;

	loc.idx = mono_metadata_token_index (index);
	loc.col_idx = MONO_INTERFACEIMPL_CLASS;
	loc.t = tdef;

	if (!mono_binary_search (&loc, tdef->base, tdef->rows, tdef->row_size, table_locator))
		return TRUE;

	start = loc.result;


	while (start > 0) {
		if (loc.idx == mono_metadata_decode_row_col (tdef, start - 1, MONO_INTERFACEIMPL_CLASS))
			start--;
		else
			break;
	}
	pos = start;
	while (pos < tdef->rows) {
		mono_metadata_decode_row (tdef, pos, cols, MONO_INTERFACEIMPL_SIZE);
		if (cols [MONO_INTERFACEIMPL_CLASS] != loc.idx)
			break;
		++pos;
	}

	if (heap_alloc_result)
		result = g_new0 (MonoClass*, pos - start);
	else
		result = (MonoClass **)mono_image_alloc0 (meta, sizeof (MonoClass*) * (pos - start));

	pos = start;
	while (pos < tdef->rows) {
		MonoClass *iface;

		mono_metadata_decode_row (tdef, pos, cols, MONO_INTERFACEIMPL_SIZE);
		if (cols [MONO_INTERFACEIMPL_CLASS] != loc.idx)
			break;
		iface = mono_class_get_and_inflate_typespec_checked (
			meta, mono_metadata_token_from_dor (cols [MONO_INTERFACEIMPL_INTERFACE]), context, error);
		if (iface == NULL)
			return FALSE;
		result [pos - start] = iface;
		++pos;
	}
	*count = pos - start;
	*interfaces = result;
	return TRUE;
}
