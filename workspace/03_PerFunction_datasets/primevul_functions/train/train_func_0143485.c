static int gfs2_rbm_find(struct gfs2_rbm *rbm, u8 state, u32 *minext,
			 const struct gfs2_inode *ip, bool nowrap)
{
	struct buffer_head *bh;
	int initial_bii;
	u32 initial_offset;
	int first_bii = rbm->bii;
	u32 first_offset = rbm->offset;
	u32 offset;
	u8 *buffer;
	int n = 0;
	int iters = rbm->rgd->rd_length;
	int ret;
	struct gfs2_bitmap *bi;
	struct gfs2_extent maxext = { .rbm.rgd = rbm->rgd, };


	if (rbm->offset != 0)
		iters++;

	while(1) {
		bi = rbm_bi(rbm);
		if (test_bit(GBF_FULL, &bi->bi_flags) &&
		    (state == GFS2_BLKST_FREE))
			goto next_bitmap;

		bh = bi->bi_bh;
		buffer = bh->b_data + bi->bi_offset;
		WARN_ON(!buffer_uptodate(bh));
		if (state != GFS2_BLKST_UNLINKED && bi->bi_clone)
			buffer = bi->bi_clone + bi->bi_offset;
		initial_offset = rbm->offset;
		offset = gfs2_bitfit(buffer, bi->bi_len, rbm->offset, state);
		if (offset == BFITNOENT)
			goto bitmap_full;
		rbm->offset = offset;
		if (ip == NULL)
			return 0;

		initial_bii = rbm->bii;
		ret = gfs2_reservation_check_and_update(rbm, ip,
							minext ? *minext : 0,
							&maxext);
		if (ret == 0)
			return 0;
		if (ret > 0) {
			n += (rbm->bii - initial_bii);
			goto next_iter;
		}
		if (ret == -E2BIG) {
			rbm->bii = 0;
			rbm->offset = 0;
			n += (rbm->bii - initial_bii);
			goto res_covered_end_of_rgrp;
		}
		return ret;

bitmap_full:
		if ((state == GFS2_BLKST_FREE) && initial_offset == 0)
			set_bit(GBF_FULL, &bi->bi_flags);

next_bitmap:
		rbm->offset = 0;
		rbm->bii++;
		if (rbm->bii == rbm->rgd->rd_length)
			rbm->bii = 0;
res_covered_end_of_rgrp:
		if ((rbm->bii == 0) && nowrap)
			break;
		n++;
next_iter:
		if (n >= iters)
			break;
	}

	if (minext == NULL || state != GFS2_BLKST_FREE)
		return -ENOSPC;


	if ((first_offset == 0) && (first_bii == 0) &&
	    (*minext < rbm->rgd->rd_extfail_pt))
		rbm->rgd->rd_extfail_pt = *minext;


	if (maxext.len) {
		*rbm = maxext.rbm;
		*minext = maxext.len;
		return 0;
	}

	return -ENOSPC;
}
