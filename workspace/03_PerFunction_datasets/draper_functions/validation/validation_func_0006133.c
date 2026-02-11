bd_queue_allocate(struct ipw2100_priv *priv,
			     struct ipw2100_bd_queue *q, int entries)
{
	IPW_DEBUG_INFO("enter\n");

	memset(q, 0, sizeof(struct ipw2100_bd_queue));

	q->entries = entries;
	q->size = entries * sizeof(struct ipw2100_bd);
	q->drv = pci_zalloc_consistent(priv->pci_dev, q->size, &q->nic);
	if (!q->drv) {
		IPW_DEBUG_INFO
		    ("can't allocate shared memory for buffer descriptors\n");
		return -ENOMEM;
	}

	IPW_DEBUG_INFO("exit\n");

	return 0;
}
