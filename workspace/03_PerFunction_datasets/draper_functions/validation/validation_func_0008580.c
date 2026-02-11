ea_set_simple(struct gfs2_inode *ip, struct buffer_head *bh,
			 struct gfs2_ea_header *ea, struct gfs2_ea_header *prev,
			 void *private)
{
	struct ea_set *es = private;
	unsigned int size;
	int stuffed;
	int error;

	stuffed = ea_calc_size(GFS2_SB(&ip->i_inode), es->es_er->er_name_len,
			       es->es_er->er_data_len, &size);

	if (ea->ea_type == GFS2_EATYPE_UNUSED) {
		if (GFS2_EA_REC_LEN(ea) < size)
			return 0;
		if (!GFS2_EA_IS_STUFFED(ea)) {
			error = ea_remove_unstuffed(ip, bh, ea, prev, 1);
			if (error)
				return error;
		}
		es->ea_split = 0;
	} else if (GFS2_EA_REC_LEN(ea) - GFS2_EA_SIZE(ea) >= size)
		es->ea_split = 1;
	else
		return 0;

	if (stuffed) {
		error = ea_set_simple_noalloc(ip, bh, ea, es);
		if (error)
			return error;
	} else {
		unsigned int blks;

		es->es_bh = bh;
		es->es_ea = ea;
		blks = 2 + DIV_ROUND_UP(es->es_er->er_data_len,
					GFS2_SB(&ip->i_inode)->sd_jbsize);

		error = ea_alloc_skeleton(ip, es->es_er, blks,
					  ea_set_simple_alloc, es);
		if (error)
			return error;
	}

	return 1;
}
