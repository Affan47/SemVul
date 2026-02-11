il_hdl_scan_results(struct il_priv *il, struct il_rx_buf *rxb)
{
#ifdef CONFIG_IWLEGACY_DEBUG
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_scanresults_notification *notif =
	    (struct il_scanresults_notification *)pkt->u.raw;

	D_SCAN("Scan ch.res: " "%d [802.11%s] " "(TSF: 0x%08X:%08X) - %d "
	       "elapsed=%lu usec\n", notif->channel, notif->band ? "bg" : "a",
	       le32_to_cpu(notif->tsf_high), le32_to_cpu(notif->tsf_low),
	       le32_to_cpu(notif->stats[0]),
	       le32_to_cpu(notif->tsf_low) - il->scan_start_tsf);
#endif
}
