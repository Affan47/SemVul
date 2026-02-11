fz_open_document(fz_context *ctx, char *filename)
{
	char *ext = strrchr(filename, '.');

	if (ext)
	{
		if (!fz_strcasecmp(ext, ".xps") || !fz_strcasecmp(ext, ".rels"))
			return (fz_document*) xps_open_document(ctx, filename);
		if (!fz_strcasecmp(ext, ".cbz") || !fz_strcasecmp(ext, ".zip"))
			return (fz_document*) cbz_open_document(ctx, filename);
		if (!fz_strcasecmp(ext, ".pdf"))
			return (fz_document*) pdf_open_document(ctx, filename);
	}


	return (fz_document*) pdf_open_document(ctx, filename);
}
