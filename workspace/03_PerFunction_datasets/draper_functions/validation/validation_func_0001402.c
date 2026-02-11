pe_image_load_pe_data (MonoImage *image)
{
	MonoCLIImageInfo *iinfo;
	MonoDotNetHeader *header;
	MonoMSDOSHeader msdos;
	gint32 offset = 0;

	iinfo = (MonoCLIImageInfo *)image->image_info;
	header = &iinfo->cli_header;

#ifdef HOST_WIN32
	if (!image->is_module_handle)
#endif
	if (offset + sizeof (msdos) > image->raw_data_len)
		goto invalid_image;
	memcpy (&msdos, image->raw_data + offset, sizeof (msdos));

	if (!(msdos.msdos_sig [0] == 'M' && msdos.msdos_sig [1] == 'Z'))
		goto invalid_image;

	msdos.pe_offset = GUINT32_FROM_LE (msdos.pe_offset);

	offset = msdos.pe_offset;

	offset = do_load_header (image, header, offset);
	if (offset < 0)
		goto invalid_image;


#if 0


	if (header->pe.pe_major != 6 || header->pe.pe_minor != 0)
		goto invalid_image;
#endif


	if (!load_section_tables (image, iinfo, offset))
		goto invalid_image;

	return TRUE;

invalid_image:
	return FALSE;
}
