afs_do_getlk(struct file *file, struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(file->f_mapping->host);
	struct key *key = file->private_data;
	int ret, lock_count;

	_enter("");

	fl->fl_type = F_UNLCK;

	mutex_lock(&vnode->vfs_inode.i_mutex);


	ret = 0;
	posix_test_lock(file, fl);
	if (fl->fl_type == F_UNLCK) {

		ret = afs_vnode_fetch_status(vnode, NULL, key);
		if (ret < 0)
			goto error;
		lock_count = vnode->status.lock_count;
		if (lock_count) {
			if (lock_count > 0)
				fl->fl_type = F_RDLCK;
			else
				fl->fl_type = F_WRLCK;
			fl->fl_start = 0;
			fl->fl_end = OFFSET_MAX;
		}
	}

error:
	mutex_unlock(&vnode->vfs_inode.i_mutex);
	_leave(" = %d [%hd]", ret, fl->fl_type);
	return ret;
}
