static inline int mnt_hold_writers(struct mount *mnt)
{
	mnt->mnt.mnt_flags |= MNT_WRITE_HOLD;


	smp_mb();


	if (mnt_get_writers(mnt) > 0)
		return -EBUSY;

	return 0;
}
