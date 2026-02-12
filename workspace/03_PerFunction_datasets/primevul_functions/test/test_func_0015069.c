static inline void mnt_unhold_writers(struct mount *mnt)
{


	smp_wmb();
	mnt->mnt.mnt_flags &= ~MNT_WRITE_HOLD;
}
