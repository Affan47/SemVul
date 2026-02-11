gkm_attribute_hash (gconstpointer v)
{
	const CK_ATTRIBUTE *a = v;
	const signed char *p;
	guint i, h;

	g_assert (a);

	p = (const signed char*)&(a->type);
	h = *p;
	for(i = 0; i < sizeof (CK_ATTRIBUTE_PTR); ++i)
		h = (h << 5) - h + *(p++);

	p = a->pValue;
	for(i = 0; i < a->ulValueLen; ++i)
		h = (h << 5) - h + *(p++);

	return h;
}
