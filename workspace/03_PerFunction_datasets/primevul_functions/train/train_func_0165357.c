void mac_drv_rx_complete(struct s_smc *smc, volatile struct s_smt_fp_rxd *rxd,
			 int frag_count, int len)
{
	skfddi_priv *bp = &smc->os;
	struct sk_buff *skb;
	unsigned char *virt, *cp;
	unsigned short ri;
	u_int RifLength;

	PRINTK(KERN_INFO "entering mac_drv_rx_complete (len=%d)\n", len);
	if (frag_count != 1) {

		printk("fddi: Multi-fragment receive!\n");
		goto RequeueRxd;

	}
	skb = rxd->rxd_os.skb;
	if (!skb) {
		PRINTK(KERN_INFO "No skb in rxd\n");
		smc->os.MacStat.gen.rx_errors++;
		goto RequeueRxd;
	}
	virt = skb->data;


	dump_data(skb->data, len);


	if ((virt[1 + 6] & FDDI_RII) == 0)
		RifLength = 0;
	else {
		int n;

		PRINTK(KERN_INFO "RIF found\n");

		cp = virt + FDDI_MAC_HDR_LEN;

		ri = ntohs(*((__be16 *) cp));
		RifLength = ri & FDDI_RCF_LEN_MASK;
		if (len < (int) (FDDI_MAC_HDR_LEN + RifLength)) {
			printk("fddi: Invalid RIF.\n");
			goto RequeueRxd;

		}
		virt[1 + 6] &= ~FDDI_RII;


		virt = cp + RifLength;
		for (n = FDDI_MAC_HDR_LEN; n; n--)
			*--virt = *--cp;

		skb_pull(skb, RifLength);
		len -= RifLength;
		RifLength = 0;
	}


	smc->os.MacStat.gen.rx_packets++;

	smc->os.MacStat.gen.rx_bytes+=len;


	if (virt[1] & 0x01) {

		smc->os.MacStat.gen.multicast++;
	}


	rxd->rxd_os.skb = NULL;
	skb_trim(skb, len);
	skb->protocol = fddi_type_trans(skb, bp->dev);

	netif_rx(skb);

	HWM_RX_CHECK(smc, RX_LOW_WATERMARK);
	return;

      RequeueRxd:
	PRINTK(KERN_INFO "Rx: re-queue RXD.\n");
	mac_drv_requeue_rxd(smc, rxd, frag_count);
	smc->os.MacStat.gen.rx_errors++;


}
