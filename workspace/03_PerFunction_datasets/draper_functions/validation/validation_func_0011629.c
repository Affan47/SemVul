ocfs2_test_bg_bit_allocatable(struct buffer_head *bg_bh,
					 int nr)
{
	struct ocfs2_group_desc *bg = (struct ocfs2_group_desc *) bg_bh->b_data;
	int ret;

	if (ocfs2_test_bit(nr, (unsigned long *)bg->bg_bitmap))
		return 0;

	if (!buffer_jbd(bg_bh))
		return 1;

	jbd_lock_bh_state(bg_bh);
	bg = (struct ocfs2_group_desc *) bh2jh(bg_bh)->b_committed_data;
	if (bg)
		ret = !ocfs2_test_bit(nr, (unsigned long *)bg->bg_bitmap);
	else
		ret = 1;
	jbd_unlock_bh_state(bg_bh);

	return ret;
}
