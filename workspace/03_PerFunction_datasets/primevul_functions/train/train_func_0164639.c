static void expire_mount(struct vfsmount *mnt, struct list_head *mounts,
				struct list_head *umounts)
{
	spin_lock(&vfsmount_lock);


	if (mnt->mnt_parent == mnt) {
		spin_unlock(&vfsmount_lock);
		return;
	}


	if (!propagate_mount_busy(mnt, 2)) {

		touch_mnt_namespace(mnt->mnt_ns);
		list_del_init(&mnt->mnt_list);
		mnt->mnt_ns = NULL;
		umount_tree(mnt, 1, umounts);
		spin_unlock(&vfsmount_lock);
	} else {


		list_add_tail(&mnt->mnt_expire, mounts);
		spin_unlock(&vfsmount_lock);
	}
}
