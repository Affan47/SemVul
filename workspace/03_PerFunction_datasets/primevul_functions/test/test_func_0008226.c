static char *sqfs_resolve_symlink(struct squashfs_symlink_inode *sym,
				  const char *base_path)
{
	char *resolved, *target;
	u32 sz;

	sz = get_unaligned_le32(&sym->symlink_size);
	target = malloc(sz + 1);
	if (!target)
		return NULL;


	target[sz] = '\0';

	strncpy(target, sym->symlink, sz);


	resolved = sqfs_get_abs_path(base_path, target);

	free(target);

	return resolved;
}
