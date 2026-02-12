static bool gfs2_rbm_incr(struct gfs2_rbm *rbm)
{
	if (rbm->offset + 1 < rbm_bi(rbm)->bi_blocks) {
		rbm->offset++;
		return false;
	}
	if (rbm->bii == rbm->rgd->rd_length - 1)
		return true;

	rbm->offset = 0;
	rbm->bii++;
	return false;
}
