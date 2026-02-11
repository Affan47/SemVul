sis190_tx_pkt_err(u32 status, struct net_device_stats *stats)
{
#define TxErrMask	(WND | TABRT | FIFO | LINK)

	if (!unlikely(status & TxErrMask))
		return 0;

	if (status & WND)
		stats->tx_window_errors++;
	if (status & TABRT)
		stats->tx_aborted_errors++;
	if (status & FIFO)
		stats->tx_fifo_errors++;
	if (status & LINK)
		stats->tx_carrier_errors++;

	stats->tx_errors++;

	return -1;
}
