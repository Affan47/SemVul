mono_image_has_authenticode_entry (MonoImage *image)
{
	MonoCLIImageInfo *iinfo = (MonoCLIImageInfo *)image->image_info;
	MonoDotNetHeader *header = &iinfo->cli_header;
	MonoPEDirEntry *de = &header->datadir.pe_certificate_table;

	return ((de->rva != 0) && (de->size > 8));
}
