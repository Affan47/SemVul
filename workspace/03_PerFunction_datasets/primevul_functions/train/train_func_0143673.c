static void sdma_make_progress(struct sdma_engine *sde, u64 status)
{
	struct sdma_txreq *txp = NULL;
	int progress = 0;
	u16 hwhead, swhead;
	int idle_check_done = 0;

	hwhead = sdma_gethead(sde);


retry:
	txp = get_txhead(sde);
	swhead = sde->descq_head & sde->sdma_mask;
	trace_hfi1_sdma_progress(sde, hwhead, swhead, txp);
	while (swhead != hwhead) {

		swhead = ++sde->descq_head & sde->sdma_mask;


		if (txp && txp->next_descq_idx == swhead) {

			sde->tx_ring[sde->tx_head++ & sde->sdma_mask] = NULL;
			complete_tx(sde, txp, SDMA_TXREQ_S_OK);

			txp = get_txhead(sde);
		}
		trace_hfi1_sdma_progress(sde, hwhead, swhead, txp);
		progress++;
	}


	if ((status & sde->idle_mask) && !idle_check_done) {
		u16 swtail;

		swtail = READ_ONCE(sde->descq_tail) & sde->sdma_mask;
		if (swtail != hwhead) {
			hwhead = (u16)read_sde_csr(sde, SD(HEAD));
			idle_check_done = 1;
			goto retry;
		}
	}

	sde->last_status = status;
	if (progress)
		sdma_desc_avail(sde, sdma_descq_freecnt(sde));
}
