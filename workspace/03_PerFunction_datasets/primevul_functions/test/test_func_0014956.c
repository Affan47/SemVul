static unsigned int recalc_flags(struct mount_kattr *kattr, struct mount *mnt)
{
	unsigned int flags = mnt->mnt.mnt_flags;


	flags &= ~kattr->attr_clr;

	flags |= kattr->attr_set;

	return flags;
}
