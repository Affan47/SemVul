ms_escher_read_ColorMRU (MSEscherState *state, MSEscherHeader *h)
{
	d (3 , {
		guint const num_Colours = h->instance;
		g_printerr ("There are %d Colours in a record with remaining length %d;\n",
			num_Colours, (h->len - COMMON_HEADER_LEN));
	});


	return FALSE;
}
