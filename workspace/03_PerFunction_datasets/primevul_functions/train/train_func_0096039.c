bool write_magic(rzip_control *control)
{
	char magic[MAGIC_LEN] = {
		'L', 'R', 'Z', 'I', LRZIP_MAJOR_VERSION, LRZIP_MINOR_VERSION
	};


	if (ENCRYPT)
		memcpy(&magic[6], &control->salt, 8);
	else if (!STDIN || !STDOUT || control->eof) {
		i64 esize = htole64(control->st_size);

		memcpy(&magic[6], &esize, 8);
	}


	if (LZMA_COMPRESS) {
		int i;

		for (i = 0; i < 5; i++)
			magic[i + 16] = (char)control->lzma_properties[i];
	}


	if (!NO_MD5)
		magic[21] = 1;
	if (ENCRYPT)
		magic[22] = 1;

	if (unlikely(fdout_seekto(control, 0)))
		fatal_return(("Failed to seek to BOF to write Magic Header\n"), false);

	if (unlikely(put_fdout(control, magic, MAGIC_LEN) != MAGIC_LEN))
		fatal_return(("Failed to write magic header\n"), false);
	control->magic_written = 1;
	return true;
}
