check_eattr_extentry(struct gfs2_inode *ip, uint64_t *ea_ptr,
			 struct gfs2_buffer_head *leaf_bh,
			 struct gfs2_ea_header *ea_hdr,
			 struct gfs2_ea_header *ea_hdr_prev, void *private)
{
	uint8_t q;
	struct gfs2_sbd *sdp = ip->i_sbd;

	q = block_type(be64_to_cpu(*ea_ptr));
	if (q != gfs2_meta_eattr) {
		if (remove_eattr_entry(sdp, leaf_bh, ea_hdr, ea_hdr_prev)){
			stack;
			return -1;
		}
		return 1;
	}
	return 0;
}
