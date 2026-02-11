get_inode_count(ext2_icount_t icount, ext2_ino_t ino,
				 __u32 *count)
{
	struct ext2_icount_el 	*el;
	TDB_DATA key, data;

	if (icount->tdb) {
		key.dptr = (unsigned char *) &ino;
		key.dsize = sizeof(ext2_ino_t);

		data = tdb_fetch(icount->tdb, key);
		if (data.dptr == NULL) {
			*count = 0;
			return tdb_error(icount->tdb) + EXT2_ET_TDB_SUCCESS;
		}

		*count = *((__u32 *) data.dptr);
		free(data.dptr);
		return 0;
	}
	el = get_icount_el(icount, ino, 0);
	if (!el) {
		*count = 0;
		return ENOENT;
	}

	*count = el->count;
	return 0;
}
