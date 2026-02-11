mt7601u_alloc_tx_queue(struct mt7601u_dev *dev,
				  struct mt7601u_tx_queue *q)
{
	int i;

	q->dev = dev;
	q->entries = N_TX_ENTRIES;

	for (i = 0; i < N_TX_ENTRIES; i++) {
		q->e[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!q->e[i].urb)
			return -ENOMEM;
	}

	return 0;
}
