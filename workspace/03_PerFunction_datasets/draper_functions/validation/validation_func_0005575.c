bnx2x_add_all_napi_cnic(struct bnx2x *bp)
{
	int i;


	for_each_rx_queue_cnic(bp, i) {
		netif_napi_add(bp->dev, &bnx2x_fp(bp, i, napi),
			       bnx2x_poll, NAPI_POLL_WEIGHT);
		napi_hash_add(&bnx2x_fp(bp, i, napi));
	}
}
