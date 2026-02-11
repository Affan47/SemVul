cramfs_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	unsigned int offset = 0;
	struct inode *inode = NULL;
	int sorted;

	mutex_lock(&read_mutex);
	sorted = CRAMFS_SB(dir->i_sb)->flags & CRAMFS_FLAG_SORTED_DIRS;
	while (offset < dir->i_size) {
		struct cramfs_inode *de;
		char *name;
		int namelen, retval;
		int dir_off = OFFSET(dir) + offset;

		de = cramfs_read(dir->i_sb, dir_off, sizeof(*de)+CRAMFS_MAXPATHLEN);
		name = (char *)(de+1);


		if (sorted && (dentry->d_name.name[0] < name[0]))
			break;

		namelen = de->namelen << 2;
		offset += sizeof(*de) + namelen;


		if (((dentry->d_name.len + 3) & ~3) != namelen)
			continue;

		for (;;) {
			if (!namelen) {
				inode = ERR_PTR(-EIO);
				goto out;
			}
			if (name[namelen-1])
				break;
			namelen--;
		}
		if (namelen != dentry->d_name.len)
			continue;
		retval = memcmp(dentry->d_name.name, name, namelen);
		if (retval > 0)
			continue;
		if (!retval) {
			inode = get_cramfs_inode(dir->i_sb, de, dir_off);
			break;
		}

		if (sorted)
			break;
	}
out:
	mutex_unlock(&read_mutex);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	d_add(dentry, inode);
	return NULL;
}
