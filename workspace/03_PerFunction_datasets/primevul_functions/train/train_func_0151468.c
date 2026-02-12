mwifiex_wmm_compute_drv_pkt_delay(struct mwifiex_private *priv,
				  const struct sk_buff *skb)
{
	u32 queue_delay = ktime_to_ms(net_timedelta(skb->tstamp));
	u8 ret_val;


	ret_val = (u8) (min(queue_delay, priv->wmm.drv_pkt_delay_max) >> 1);

	mwifiex_dbg(priv->adapter, DATA, "data: WMM: Pkt Delay: %d ms,\t"
		    "%d ms sent to FW\n", queue_delay, ret_val);

	return ret_val;
}
