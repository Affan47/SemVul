release_card(struct w6692_hw *card)
{
	u_long	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	w6692_mode(&card->bc[0], ISDN_P_NONE);
	w6692_mode(&card->bc[1], ISDN_P_NONE);
	if ((card->fmask & led) || card->subtype == W6692_USR) {
		card->xdata |= 0x04;
		WriteW6692(card, W_XDATA, card->xdata);
	}
	spin_unlock_irqrestore(&card->lock, flags);
	free_irq(card->irq, card);
	l1_event(card->dch.l1, CLOSE_CHANNEL);
	mISDN_unregister_device(&card->dch.dev);
	release_region(card->addr, 256);
	mISDN_freebchannel(&card->bc[1].bch);
	mISDN_freebchannel(&card->bc[0].bch);
	mISDN_freedchannel(&card->dch);
	write_lock_irqsave(&card_lock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&card_lock, flags);
	pci_disable_device(card->pdev);
	pci_set_drvdata(card->pdev, NULL);
	kfree(card);
}
