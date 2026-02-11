p80211netdev_rx_bh(unsigned long arg)
{
	wlandevice_t *wlandev = (wlandevice_t *) arg;
	struct sk_buff *skb = NULL;
	netdevice_t *dev = wlandev->netdev;


	while ((skb = skb_dequeue(&wlandev->nsd_rxq))) {
		if (wlandev->state == WLAN_DEVICE_OPEN) {

			if (dev->type != ARPHRD_ETHER) {


				skb->dev = dev;
				skb_reset_mac_header(skb);
				skb->ip_summed = CHECKSUM_NONE;
				skb->pkt_type = PACKET_OTHERHOST;
				skb->protocol = htons(ETH_P_80211_RAW);
				dev->last_rx = jiffies;

				dev->stats.rx_packets++;
				dev->stats.rx_bytes += skb->len;
				netif_rx_ni(skb);
				continue;
			} else {
				if (!p80211_convert_to_ether(wlandev, skb))
					continue;
			}
		}
		dev_kfree_skb(skb);
	}
}
