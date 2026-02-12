static int ext4_bh_unmapped_or_delay(handle_t *handle, struct buffer_head *bh)
{


	return ((!buffer_mapped(bh) || buffer_delay(bh)) && buffer_dirty(bh));
}
