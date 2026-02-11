qpro_check_signature (GsfInput *input)
{
	guint8 const *header;
	guint16 version;

	if (gsf_input_seek (input, 0, G_SEEK_SET) ||
	    NULL == (header = gsf_input_read (input, 2+2+2, NULL)) ||
	    GSF_LE_GET_GUINT16 (header + 0) != 0 ||
	    GSF_LE_GET_GUINT16 (header + 2) != 2)
		return FALSE;
	version = GSF_LE_GET_GUINT16 (header + 4);
	return (version == 0x1001 ||
		version == 0x1002 ||
		version == 0x1006 ||
		version == 0x1007);
}
