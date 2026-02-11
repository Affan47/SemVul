rsi_prepare_skb(struct rsi_common *common,
				       u8 *buffer,
				       u32 pkt_len,
				       u8 extended_desc)
{
	struct ieee80211_tx_info *info;
	struct skb_info *rx_params;
	struct sk_buff *skb = NULL;
	u8 payload_offset;

	if (WARN(!pkt_len, "%s: Dummy pkt received", __func__))
		return NULL;

	if (pkt_len > (RSI_RCV_BUFFER_LEN * 4)) {
		rsi_dbg(ERR_ZONE, "%s: Pkt size > max rx buf size %d\n",
			__func__, pkt_len);
		pkt_len = RSI_RCV_BUFFER_LEN * 4;
	}

	pkt_len -= extended_desc;
	skb = dev_alloc_skb(pkt_len + FRAME_DESC_SZ);
	if (skb == NULL)
		return NULL;

	payload_offset = (extended_desc + FRAME_DESC_SZ);
	skb_put(skb, pkt_len);
	memcpy((skb->data), (buffer + payload_offset), skb->len);

	info = IEEE80211_SKB_CB(skb);
	rx_params = (struct skb_info *)info->driver_data;
	rx_params->rssi = rsi_get_rssi(buffer);
	rx_params->channel = rsi_get_connected_channel(common->priv);

	return skb;
}
