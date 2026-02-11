qxl_ttm_tt_populate(struct ttm_tt *ttm)
{
	int r;

	if (ttm->state != tt_unpopulated)
		return 0;

	r = ttm_pool_populate(ttm);
	if (r)
		return r;

	return 0;
}
