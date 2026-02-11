save_image_file_to_dir(struct image_file *imf, char *outf,
				   int (* progress)(char *msg, void *data), void *data)
{
	char fn[16384], ifn[16384];
	int i;
	char msg[256];

	g_return_val_if_fail(imf != NULL, -1);
	g_return_val_if_fail(imf->fr != NULL, -1);
	g_return_val_if_fail(outf != NULL, -1);

	if (imf->flags & IMG_SKIP)
		return 0;
	strncpy(ifn, imf->filename, 16383);
	ifn[16383] = 0;
	snprintf(fn, 16383, "%s/%s", outf, basename(ifn));
	if (progress) {
		snprintf(msg, 255, " saving %s\n", fn);
		if ((* progress)(msg, data))
			return -1;
	}
	if (is_zip_name(fn)) {
		for (i = strlen(fn); i > 0; i--)
			if (fn[i] == '.') {
				fn[i] = 0;
				break;
			}
		return write_gz_fits_frame(imf->fr, fn, P_STR(FILE_COMPRESS));
	} else {
		return write_fits_frame(imf->fr, fn);
	}
}
