static void do_idmap_mount(const struct mount_kattr *kattr, struct mount *mnt)
{
	struct user_namespace *mnt_userns;

	if (!kattr->mnt_userns)
		return;

	mnt_userns = get_user_ns(kattr->mnt_userns);

	smp_store_release(&mnt->mnt.mnt_userns, mnt_userns);
}
