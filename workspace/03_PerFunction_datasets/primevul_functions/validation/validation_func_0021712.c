ms_escher_read_ChildAnchor (MSEscherState *state, MSEscherHeader *h)
{
	gboolean needs_free;
	int len = h->len - COMMON_HEADER_LEN;
	guint8 const *data = ms_escher_get_data (state,
		h->offset + COMMON_HEADER_LEN, len, &needs_free);


	d (1, {
		g_print ("ChildAnchor");
		gsf_mem_dump (data, len);});

	if (needs_free)
		g_free ((guint8 *)data);
	return FALSE;
}
