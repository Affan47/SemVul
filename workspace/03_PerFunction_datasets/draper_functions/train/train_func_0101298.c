rsxx_eeh_frozen(struct pci_dev *dev)
{
	struct rsxx_cardinfo *card = pci_get_drvdata(dev);
	int i;
	int st;

	dev_warn(&dev->dev, "IBM Flash Adapter PCI: preparing for slot reset.\n");

	card->eeh_state = 1;
	rsxx_mask_interrupts(card);


	wmb();

	pci_disable_device(dev);

	st = rsxx_eeh_save_issued_dmas(card);
	if (st)
		return st;

	rsxx_eeh_save_issued_creg(card);

	for (i = 0; i < card->n_targets; i++) {
		if (card->ctrl[i].status.buf)
			pci_free_consistent(card->dev, STATUS_BUFFER_SIZE8,
					    card->ctrl[i].status.buf,
					    card->ctrl[i].status.dma_addr);
		if (card->ctrl[i].cmd.buf)
			pci_free_consistent(card->dev, COMMAND_BUFFER_SIZE8,
					    card->ctrl[i].cmd.buf,
					    card->ctrl[i].cmd.dma_addr);
	}

	return 0;
}
