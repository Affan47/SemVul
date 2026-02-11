iswritefileempty (struct uae_prefs *p, const TCHAR *name)
{
	struct zfile *zf;
	bool wrprot;
	uae_char buffer[8];
	trackid td[MAX_TRACKS];
	int tracks, ddhd, i, ret;

	zf = getwritefile (p, name, &wrprot);
	if (!zf) return 1;
	zfile_fread (buffer, sizeof (char), 8, zf);
	if (strncmp ((uae_char*)buffer, "UAE-1ADF", 8))
		return 0;
	ret = read_header_ext2 (zf, td, &tracks, &ddhd);
	zfile_fclose (zf);
	if (!ret)
		return 1;
	for (i = 0; i < tracks; i++) {
		if (td[i].bitlen) return 0;
	}
	return 1;
}
