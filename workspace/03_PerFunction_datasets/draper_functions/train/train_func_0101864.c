bnxt_unregister_dev(struct bnxt_en_dev *edev, int ulp_id)
{
	struct net_device *dev = edev->net;
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_ulp *ulp;
	int i = 0;

	ASSERT_RTNL();
	if (ulp_id >= BNXT_MAX_ULP)
		return -EINVAL;

	ulp = &edev->ulp_tbl[ulp_id];
	if (!rcu_access_pointer(ulp->ulp_ops)) {
		netdev_err(bp->dev, "ulp id %d not registered\n", ulp_id);
		return -EINVAL;
	}
	if (ulp_id == BNXT_ROCE_ULP) {
		unsigned int max_stat_ctxs;

		max_stat_ctxs = bnxt_get_max_func_stat_ctxs(bp);
		bnxt_set_max_func_stat_ctxs(bp, max_stat_ctxs + 1);
	}
	if (ulp->max_async_event_id)
		bnxt_hwrm_func_rgtr_async_events(bp, NULL, 0);

	RCU_INIT_POINTER(ulp->ulp_ops, NULL);
	synchronize_rcu();
	ulp->max_async_event_id = 0;
	ulp->async_events_bmap = NULL;
	while (atomic_read(&ulp->ref_count) != 0 && i < 10) {
		msleep(100);
		i++;
	}
	return 0;
}
