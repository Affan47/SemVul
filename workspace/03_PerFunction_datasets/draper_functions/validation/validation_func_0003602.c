process_cmdtypedata(int recvlength, struct sk_buff *skb,
				       struct if_usb_card *cardp,
				       struct lbs_private *priv)
{
	if (recvlength > MRVDRV_ETH_RX_PACKET_BUFFER_SIZE + MESSAGE_HEADER_LEN
	    || recvlength < MRVDRV_MIN_PKT_LEN) {
		lbs_deb_usbd(&cardp->udev->dev, "Packet length is Invalid\n");
		kfree_skb(skb);
		return;
	}

	skb_reserve(skb, IPFIELD_ALIGN_OFFSET);
	skb_put(skb, recvlength);
	skb_pull(skb, MESSAGE_HEADER_LEN);

	lbs_process_rxed_packet(priv, skb);
}
