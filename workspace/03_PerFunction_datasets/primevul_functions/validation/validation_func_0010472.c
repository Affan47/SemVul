void fuse_release_common(struct file *file, bool isdir)
{
	struct fuse_inode *fi = get_fuse_inode(file_inode(file));
	struct fuse_file *ff = file->private_data;
	struct fuse_release_args *ra = ff->release_args;
	int opcode = isdir ? FUSE_RELEASEDIR : FUSE_RELEASE;

	fuse_prepare_release(fi, ff, file->f_flags, opcode);

	if (ff->flock) {
		ra->inarg.release_flags |= FUSE_RELEASE_FLOCK_UNLOCK;
		ra->inarg.lock_owner = fuse_lock_owner_id(ff->fm->fc,
							  (fl_owner_t) file);
	}

	ra->inode = igrab(file_inode(file));


	fuse_file_put(ff, ff->fm->fc->destroy, isdir);
}
