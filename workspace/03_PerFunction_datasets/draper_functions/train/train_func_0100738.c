file_object_alloc(const int fd, const char * const pathname, int accmode)
{
	static const struct file_object zero_fo;
	struct file_object *fo;
	hikset_t *ht;

	g_return_val_if_fail(fd >= 0, NULL);
	g_return_val_if_fail(pathname, NULL);
	g_return_val_if_fail(is_absolute_path(pathname), NULL);
	g_return_val_if_fail(!file_object_find(pathname, accmode), NULL);

	ht = file_object_mode_get_table(accmode);
	g_return_val_if_fail(ht, NULL);

	WALLOC(fo);
	*fo = zero_fo;
	fo->magic = FILE_OBJECT_MAGIC;
	fo->ref_count = 1;
	fo->fd = fd;
	fo->accmode = accmode;
	fo->pathname = atom_str_get(pathname);

	file_object_check(fo);
	g_assert(is_valid_fd(fo->fd));
	hikset_insert(ht, fo);

	return fo;
}
