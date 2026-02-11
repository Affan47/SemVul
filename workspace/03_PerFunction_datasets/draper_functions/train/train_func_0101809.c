xircom_close(struct net_device *dev)
{
	struct xircom_private *card;
	unsigned long flags;

	card = netdev_priv(dev);
	netif_stop_queue(dev);


	spin_lock_irqsave(&card->lock,flags);

	disable_all_interrupts(card);
#if 0

	deactivate_receiver(card);
	deactivate_transmitter(card);
#endif
	remove_descriptors(card);

	spin_unlock_irqrestore(&card->lock,flags);

	card->open = 0;
	free_irq(card->pdev->irq, dev);

	return 0;

}
