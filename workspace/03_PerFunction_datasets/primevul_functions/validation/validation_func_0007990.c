static int follow_managed(struct path *path, struct nameidata *nd)
{
	struct vfsmount *mnt = path->mnt;
	unsigned flags;
	bool need_mntput = false;
	int ret = 0;


	while (flags = smp_load_acquire(&path->dentry->d_flags),
	       unlikely(flags & DCACHE_MANAGED_DENTRY)) {


		if (flags & DCACHE_MANAGE_TRANSIT) {
			BUG_ON(!path->dentry->d_op);
			BUG_ON(!path->dentry->d_op->d_manage);
			ret = path->dentry->d_op->d_manage(path, false);
			flags = smp_load_acquire(&path->dentry->d_flags);
			if (ret < 0)
				break;
		}


		if (flags & DCACHE_MOUNTED) {
			struct vfsmount *mounted = lookup_mnt(path);
			if (mounted) {
				dput(path->dentry);
				if (need_mntput)
					mntput(path->mnt);
				path->mnt = mounted;
				path->dentry = dget(mounted->mnt_root);
				need_mntput = true;
				continue;
			}


		}


		if (flags & DCACHE_NEED_AUTOMOUNT) {
			ret = follow_automount(path, nd, &need_mntput);
			if (ret < 0)
				break;
			continue;
		}


		break;
	}

	if (need_mntput && path->mnt == mnt)
		mntput(path->mnt);
	if (need_mntput)
		nd->flags |= LOOKUP_JUMPED;
	if (ret == -EISDIR || !ret)
		ret = 1;
	if (ret > 0 && unlikely(d_flags_negative(flags)))
		ret = -ENOENT;
	if (unlikely(ret < 0))
		path_put_conditional(path, nd);
	return ret;
}
