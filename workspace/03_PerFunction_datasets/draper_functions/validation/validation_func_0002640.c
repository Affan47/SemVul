enumerate_and_find_object (CK_OBJECT_HANDLE object, GckAttributes *attrs, gpointer user_data)
{
	FindObject *ctx = user_data;
	CK_ATTRIBUTE_PTR match;
	const GckAttribute *attr;
	CK_ULONG i;

	for (i = 0; i < ctx->n_attrs; ++i) {
		match = ctx->attrs + i;
		attr = gck_attributes_find (attrs, match->type);
		if (!attr)
			return TRUE;

		if (attr->length != match->ulValueLen ||
		    memcmp (attr->value, match->pValue, attr->length) != 0)
			return TRUE;
	}

	ctx->object = object;
	return FALSE;
}
