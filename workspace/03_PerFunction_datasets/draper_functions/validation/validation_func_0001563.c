gfs2_log_get_bio(struct gfs2_sbd *sdp, u64 blkno)
{
	struct bio *bio = sdp->sd_log_bio;
	u64 nblk;

	if (bio) {
		nblk = bio_end_sector(bio);
		nblk >>= sdp->sd_fsb2bb_shift;
		if (blkno == nblk)
			return bio;
		gfs2_log_flush_bio(sdp, WRITE);
	}

	return gfs2_log_alloc_bio(sdp, blkno);
}
