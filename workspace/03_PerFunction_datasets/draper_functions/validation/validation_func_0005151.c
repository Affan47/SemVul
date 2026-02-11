jme_tx_clean_tasklet(unsigned long arg)
{
	struct jme_adapter *jme = (struct jme_adapter *)arg;
	struct jme_ring *txring = &(jme->txring[0]);
	struct txdesc *txdesc = txring->desc;
	struct jme_buffer_info *txbi = txring->bufinf, *ctxbi, *ttxbi;
	int i, j, cnt = 0, max, err, mask;

	tx_dbg(jme, "Into txclean\n");

	if (unlikely(!atomic_dec_and_test(&jme->tx_cleaning)))
		goto out;

	if (unlikely(atomic_read(&jme->link_changing) != 1))
		goto out;

	if (unlikely(!netif_carrier_ok(jme->dev)))
		goto out;

	max = jme->tx_ring_size - atomic_read(&txring->nr_free);
	mask = jme->tx_ring_mask;

	for (i = atomic_read(&txring->next_to_clean) ; cnt < max ; ) {

		ctxbi = txbi + i;

		if (likely(ctxbi->skb &&
		!(txdesc[i].descwb.flags & TXWBFLAG_OWN))) {

			tx_dbg(jme, "txclean: %d+%d@%lu\n",
			       i, ctxbi->nr_desc, jiffies);

			err = txdesc[i].descwb.flags & TXWBFLAG_ALLERR;

			for (j = 1 ; j < ctxbi->nr_desc ; ++j) {
				ttxbi = txbi + ((i + j) & (mask));
				txdesc[(i + j) & (mask)].dw[0] = 0;

				pci_unmap_page(jme->pdev,
						 ttxbi->mapping,
						 ttxbi->len,
						 PCI_DMA_TODEVICE);

				ttxbi->mapping = 0;
				ttxbi->len = 0;
			}

			dev_kfree_skb(ctxbi->skb);

			cnt += ctxbi->nr_desc;

			if (unlikely(err)) {
				++(NET_STAT(jme).tx_carrier_errors);
			} else {
				++(NET_STAT(jme).tx_packets);
				NET_STAT(jme).tx_bytes += ctxbi->len;
			}

			ctxbi->skb = NULL;
			ctxbi->len = 0;
			ctxbi->start_xmit = 0;

		} else {
			break;
		}

		i = (i + ctxbi->nr_desc) & mask;

		ctxbi->nr_desc = 0;
	}

	tx_dbg(jme, "txclean: done %d@%lu\n", i, jiffies);
	atomic_set(&txring->next_to_clean, i);
	atomic_add(cnt, &txring->nr_free);

	jme_wake_queue_if_stopped(jme);

out:
	atomic_inc(&jme->tx_cleaning);
}
