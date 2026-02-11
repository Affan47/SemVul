zfile_fwrite (const void *b, size_t l1, size_t l2, struct zfile *z)
{
	if (z->archiveparent)
		return 0;
	if (z->zfilewrite)
		return z->zfilewrite (b, l1, l2, z);
	if (z->parent && z->useparent)
		return 0;
	if (z->data) {
		uae_s64 off = z->seek + l1 * l2;
		if (z->allocsize == 0) {
			write_log (_T("zfile_fwrite(data,%s) but allocsize=0!\n"), z->name);
			return 0;
		}
		if (off > z->allocsize) {
			if (z->allocsize < off)
				z->allocsize = off;
			z->allocsize += z->size / 2;
			if (z->allocsize < 10000)
				z->allocsize = 10000;
			z->data = xrealloc (uae_u8, z->data, z->allocsize);
			z->datasize = z->size = off;
		}
		memcpy (z->data + z->seek, b, l1 * l2);
		z->seek += l1 * l2;
		if (z->seek > z->size)
			z->size = z->seek;
		if (z->size > z->datasize)
			z->datasize = z->size;
		return l2;
	}
	return fwrite (b, l1, l2, z->f);
}
