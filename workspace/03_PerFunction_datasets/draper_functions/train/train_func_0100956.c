sxgbe_get_rx_ctxt_tstamp_status(struct sxgbe_rx_ctxt_desc *p)
{
	if ((p->tstamp_hi == 0xffffffff) && (p->tstamp_lo == 0xffffffff)) {
		pr_err("Time stamp corrupted\n");
		return 0;
	}

	return p->tstamp_available;
}
