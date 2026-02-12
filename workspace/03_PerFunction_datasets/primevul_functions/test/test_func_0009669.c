void rtrs_clt_put_permit(struct rtrs_clt_sess *clt,
			 struct rtrs_permit *permit)
{
	if (WARN_ON(!test_bit(permit->mem_id, clt->permits_map)))
		return;

	__rtrs_put_permit(clt, permit);


	if (waitqueue_active(&clt->permits_wait))
		wake_up(&clt->permits_wait);
}
