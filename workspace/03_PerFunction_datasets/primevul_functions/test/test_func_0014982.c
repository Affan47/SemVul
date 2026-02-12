static int do_mount_setattr(struct path *path, struct mount_kattr *kattr)
{
	struct mount *mnt = real_mount(path->mnt), *last = NULL;
	int err = 0;

	if (path->dentry != mnt->mnt.mnt_root)
		return -EINVAL;

	if (kattr->propagation) {


		namespace_lock();
		if (kattr->propagation == MS_SHARED) {
			err = invent_group_ids(mnt, kattr->recurse);
			if (err) {
				namespace_unlock();
				return err;
			}
		}
	}

	lock_mount_hash();


	last = mount_setattr_prepare(kattr, mnt, &err);
	if (last)
		mount_setattr_commit(kattr, mnt, last, err);

	unlock_mount_hash();

	if (kattr->propagation) {
		namespace_unlock();
		if (err)
			cleanup_group_ids(mnt, NULL);
	}

	return err;
}
