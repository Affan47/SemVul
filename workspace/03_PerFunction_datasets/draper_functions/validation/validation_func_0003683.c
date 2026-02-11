bnx2_poll(struct nic* nic, int retrieve)
{
	struct bnx2 *bp = &bnx2;
	struct rx_bd *cons_bd, *prod_bd;
	u16 hw_cons, sw_cons, sw_ring_cons, sw_prod, sw_ring_prod;
	struct l2_fhdr *rx_hdr;
	int result = 0;
	unsigned int len;
	unsigned char *data;
	u32 status;

#if 0
	if ((bp->status_blk->status_idx == bp->last_status_idx) &&
	    (REG_RD(bp, BNX2_PCICFG_MISC_STATUS) &
	     BNX2_PCICFG_MISC_STATUS_INTA_VALUE)) {

		bp->last_status_idx = bp->status_blk->status_idx;
		REG_WR(bp, BNX2_PCICFG_INT_ACK_CMD,
	       BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
	       BNX2_PCICFG_INT_ACK_CMD_MASK_INT |
	       bp->last_status_idx);
		return 0;
	}
#endif

	if ((bp->status_blk->status_rx_quick_consumer_index0 != bp->rx_cons) && !retrieve)
		return 1;

	if (bp->status_blk->status_rx_quick_consumer_index0 != bp->rx_cons) {

		hw_cons = bp->hw_rx_cons = bp->status_blk->status_rx_quick_consumer_index0;
		if ((hw_cons & MAX_RX_DESC_CNT) == MAX_RX_DESC_CNT) {
			hw_cons++;
		}
		sw_cons = bp->rx_cons;
		sw_prod = bp->rx_prod;

		rmb();
		if (sw_cons != hw_cons) {

			sw_ring_cons = RX_RING_IDX(sw_cons);
			sw_ring_prod = RX_RING_IDX(sw_prod);

			data = bus_to_virt(bp->rx_desc_ring[sw_ring_cons].rx_bd_haddr_lo);

			rx_hdr = (struct l2_fhdr *)data;
			len = rx_hdr->l2_fhdr_pkt_len - 4;
			if ((len > (ETH_MAX_MTU + ETH_HLEN)) ||
				((status = rx_hdr->l2_fhdr_status) &
				(L2_FHDR_ERRORS_BAD_CRC |
				L2_FHDR_ERRORS_PHY_DECODE |
				L2_FHDR_ERRORS_ALIGNMENT |
				L2_FHDR_ERRORS_TOO_SHORT |
				L2_FHDR_ERRORS_GIANT_FRAME))) {
				result = 0;
			}
			else
			{
				nic->packetlen = len;
				memcpy(nic->packet, data + bp->rx_offset, len);
				result = 1;
			}


			bp->rx_prod_bseq += bp->rx_buf_use_size;
			if (sw_cons != sw_prod) {
				cons_bd = &bp->rx_desc_ring[sw_ring_cons];
				prod_bd = &bp->rx_desc_ring[sw_ring_prod];
				prod_bd->rx_bd_haddr_hi = 0;
				prod_bd->rx_bd_haddr_lo = cons_bd->rx_bd_haddr_lo;
			}

			sw_cons = NEXT_RX_BD(sw_cons);
			sw_prod = NEXT_RX_BD(sw_prod);

		}

		bp->rx_cons = sw_cons;
		bp->rx_prod = sw_prod;

		REG_WR16(bp, MB_RX_CID_ADDR + BNX2_L2CTX_HOST_BDIDX, bp->rx_prod);

		REG_WR(bp, MB_RX_CID_ADDR + BNX2_L2CTX_HOST_BSEQ, bp->rx_prod_bseq);

		wmb();

	}

	bnx2_poll_link(bp);

#if 0
	bp->last_status_idx = bp->status_blk->status_idx;
	rmb();

	REG_WR(bp, BNX2_PCICFG_INT_ACK_CMD,
	       BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID |
	       BNX2_PCICFG_INT_ACK_CMD_MASK_INT |
	       bp->last_status_idx);

	REG_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd | BNX2_HC_COMMAND_COAL_NOW_WO_INT);
#endif

	return result;
}
