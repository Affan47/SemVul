static struct btrfs_bio *alloc_btrfs_bio(int total_stripes, int real_stripes)
{
	struct btrfs_bio *bbio = kzalloc(

		sizeof(struct btrfs_bio) +

		sizeof(struct btrfs_bio_stripe) * (total_stripes) +

		sizeof(int) * (real_stripes) +


		sizeof(u64) * (total_stripes),
		GFP_NOFS|__GFP_NOFAIL);

	atomic_set(&bbio->error, 0);
	refcount_set(&bbio->refs, 1);

	bbio->tgtdev_map = (int *)(bbio->stripes + total_stripes);
	bbio->raid_map = (u64 *)(bbio->tgtdev_map + real_stripes);

	return bbio;
}
