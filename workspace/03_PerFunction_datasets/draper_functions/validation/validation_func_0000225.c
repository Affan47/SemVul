nilfs_fh_to_dentry(struct super_block *sb, struct fid *fh,
					 int fh_len, int fh_type)
{
	struct nilfs_fid *fid = (struct nilfs_fid *)fh;

	if (fh_len < NILFS_FID_SIZE_NON_CONNECTABLE ||
	    (fh_type != FILEID_NILFS_WITH_PARENT &&
	     fh_type != FILEID_NILFS_WITHOUT_PARENT))
		return NULL;

	return nilfs_get_dentry(sb, fid->cno, fid->ino, fid->gen);
}
