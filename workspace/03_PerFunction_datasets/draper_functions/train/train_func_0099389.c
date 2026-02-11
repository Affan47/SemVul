brcmf_sdio_sendfromq(struct brcmf_sdio *bus, uint maxframes)
{
	struct sk_buff *pkt;
	struct sk_buff_head pktq;
	u32 intstatus = 0;
	int ret = 0, prec_out, i;
	uint cnt = 0;
	u8 tx_prec_map, pkt_num;

	brcmf_dbg(TRACE, "Enter\n");

	tx_prec_map = ~bus->flowcontrol;


	for (cnt = 0; (cnt < maxframes) && data_ok(bus);) {
		pkt_num = 1;
		if (bus->txglom)
			pkt_num = min_t(u8, bus->tx_max - bus->tx_seq,
					bus->sdiodev->txglomsz);
		pkt_num = min_t(u32, pkt_num,
				brcmu_pktq_mlen(&bus->txq, ~bus->flowcontrol));
		__skb_queue_head_init(&pktq);
		spin_lock_bh(&bus->txq_lock);
		for (i = 0; i < pkt_num; i++) {
			pkt = brcmu_pktq_mdeq(&bus->txq, tx_prec_map,
					      &prec_out);
			if (pkt == NULL)
				break;
			__skb_queue_tail(&pktq, pkt);
		}
		spin_unlock_bh(&bus->txq_lock);
		if (i == 0)
			break;

		ret = brcmf_sdio_txpkt(bus, &pktq, SDPCM_DATA_CHANNEL);

		cnt += i;


		if (!bus->intr) {

			sdio_claim_host(bus->sdiodev->func[1]);
			ret = r_sdreg32(bus, &intstatus,
					offsetof(struct sdpcmd_regs,
						 intstatus));
			sdio_release_host(bus->sdiodev->func[1]);
			bus->sdcnt.f2txdata++;
			if (ret != 0)
				break;
			if (intstatus & bus->hostintmask)
				atomic_set(&bus->ipend, 1);
		}
	}


	if ((bus->sdiodev->state == BRCMF_SDIOD_DATA) &&
	    bus->txoff && (pktq_len(&bus->txq) < TXLOW)) {
		bus->txoff = false;
		brcmf_txflowblock(bus->sdiodev->dev, false);
	}

	return cnt;
}
