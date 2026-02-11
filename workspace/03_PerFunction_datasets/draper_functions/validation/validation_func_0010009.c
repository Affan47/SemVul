bsched_bio_remove(bsched_bws_t bws, bio_source_t *bio)
{
	bsched_t *bs;

	bs = bsched_get(bws);
	bio_check(bio);

	bs->sources = g_list_remove(bs->sources, bio);
	bs->count--;

	if (bs->count)
		bs->bw_slot = (bs->bw_max + bs->bw_stolen) / bs->count;

	g_assert(bs->count >= 0);
}
