nvram_write (int offset, int len)
{
	struct zfile *f;

	if (!currprefs.cs_cd32nvram)
		return;
	f = zfile_fopen (currprefs.flashfile, _T("rb+"), ZFD_NORMAL);
	if (!f) {
		f = zfile_fopen (currprefs.flashfile, _T("wb"), 0);
		if (!f) return;
		zfile_fwrite (cd32_nvram, NVRAM_SIZE, 1, f);
	}
	zfile_fseek (f, offset, SEEK_SET);
	zfile_fwrite (cd32_nvram + offset, len, 1, f);
	zfile_fclose (f);
}
