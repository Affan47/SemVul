mnt_copy_fs(struct libmnt_fs *dest,
			      const struct libmnt_fs *src)
{
	const struct libmnt_fs *org = dest;

	if (!dest) {
		dest = mnt_new_fs();
		if (!dest)
			return NULL;
	}


	dest->id         = src->id;
	dest->parent     = src->parent;
	dest->devno      = src->devno;

	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, source)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, tagname)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, tagval)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, root)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, target)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, fstype)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, optstr)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, vfs_optstr)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, fs_optstr)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, user_optstr)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, attrs)))
		goto err;
	if (cpy_str_at_offset(dest, src, offsetof(struct libmnt_fs, bindsrc)))
		goto err;

	dest->freq       = src->freq;
	dest->passno     = src->passno;
	dest->flags      = src->flags;

	return dest;
err:
	if (!org)
		mnt_free_fs(dest);
	return NULL;
}
