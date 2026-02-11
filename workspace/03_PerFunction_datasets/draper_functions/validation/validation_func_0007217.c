GdipCreateMetafileFromFile (GDIPCONST WCHAR *file, GpMetafile **metafile)
{
	FILE *fp;
	char *file_name;
	GpStatus status = GenericError;

	if (!file || !metafile)
		return InvalidParameter;

	file_name = (char *) ucs2_to_utf8 ((const gunichar2 *)file, -1);
	if (!file_name)
		return InvalidParameter;

	fp = fopen (file_name, "rb");
	if (fp) {
		status = gdip_get_metafile_from (fp, metafile, File);
		fclose (fp);
	}
	GdipFree (file_name);
	return status;
}
