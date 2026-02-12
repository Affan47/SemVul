static void scrub_wr_submit(struct scrub_ctx *sctx)
{
	struct scrub_bio *sbio;

	if (!sctx->wr_curr_bio)
		return;

	sbio = sctx->wr_curr_bio;
	sctx->wr_curr_bio = NULL;
	WARN_ON(!sbio->bio->bi_disk);
	scrub_pending_bio_inc(sctx);


	btrfsic_submit_bio(sbio->bio);
}
