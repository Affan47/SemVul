nilfs_bmap_seek_key(struct nilfs_bmap *bmap, __u64 start, __u64 *keyp)
{
	int ret;

	down_read(&bmap->b_sem);
	ret = bmap->b_ops->bop_seek_key(bmap, start, keyp);
	up_read(&bmap->b_sem);

	if (ret < 0)
		ret = nilfs_bmap_convert_error(bmap, __func__, ret);
	return ret;
}
