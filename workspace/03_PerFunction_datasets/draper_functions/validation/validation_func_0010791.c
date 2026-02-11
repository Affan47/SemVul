bnxt_rx_pages(struct bnxt *bp, struct bnxt_napi *bnapi,
				     struct sk_buff *skb, u16 cp_cons,
				     u32 agg_bufs)
{
	struct pci_dev *pdev = bp->pdev;
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	u16 prod = rxr->rx_agg_prod;
	u32 i;

	for (i = 0; i < agg_bufs; i++) {
		u16 cons, frag_len;
		struct rx_agg_cmp *agg;
		struct bnxt_sw_rx_agg_bd *cons_rx_buf;
		struct page *page;
		dma_addr_t mapping;

		agg = (struct rx_agg_cmp *)
			&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];
		cons = agg->rx_agg_cmp_opaque;
		frag_len = (le32_to_cpu(agg->rx_agg_cmp_len_flags_type) &
			    RX_AGG_CMP_LEN) >> RX_AGG_CMP_LEN_SHIFT;

		cons_rx_buf = &rxr->rx_agg_ring[cons];
		skb_fill_page_desc(skb, i, cons_rx_buf->page,
				   cons_rx_buf->offset, frag_len);
		__clear_bit(cons, rxr->rx_agg_bmap);


		mapping = cons_rx_buf->mapping;
		page = cons_rx_buf->page;
		cons_rx_buf->page = NULL;

		if (bnxt_alloc_rx_page(bp, rxr, prod, GFP_ATOMIC) != 0) {
			struct skb_shared_info *shinfo;
			unsigned int nr_frags;

			shinfo = skb_shinfo(skb);
			nr_frags = --shinfo->nr_frags;
			__skb_frag_set_page(&shinfo->frags[nr_frags], NULL);

			dev_kfree_skb(skb);

			cons_rx_buf->page = page;


			rxr->rx_agg_prod = prod;
			bnxt_reuse_rx_agg_bufs(bnapi, cp_cons, agg_bufs - i);
			return NULL;
		}

		dma_unmap_page(&pdev->dev, mapping, BNXT_RX_PAGE_SIZE,
			       PCI_DMA_FROMDEVICE);

		skb->data_len += frag_len;
		skb->len += frag_len;
		skb->truesize += PAGE_SIZE;

		prod = NEXT_RX_AGG(prod);
		cp_cons = NEXT_CMP(cp_cons);
	}
	rxr->rx_agg_prod = prod;
	return skb;
}
