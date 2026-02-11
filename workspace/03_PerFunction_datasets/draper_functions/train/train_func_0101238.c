free_rx_slot(struct dln2_dev *dln2, u16 handle, int slot)
{
	struct dln2_mod_rx_slots *rxs;
	struct urb *urb = NULL;
	unsigned long flags;
	struct dln2_rx_context *rxc;

	rxs = &dln2->mod_rx_slots[handle];

	spin_lock_irqsave(&rxs->lock, flags);

	clear_bit(slot, rxs->bmap);

	rxc = &rxs->slots[slot];
	rxc->in_use = false;
	urb = rxc->urb;
	rxc->urb = NULL;
	reinit_completion(&rxc->done);

	spin_unlock_irqrestore(&rxs->lock, flags);

	if (urb) {
		int err;
		struct device *dev = &dln2->interface->dev;

		err = usb_submit_urb(urb, GFP_KERNEL);
		if (err < 0)
			dev_err(dev, "failed to resubmit RX URB: %d\n", err);
	}

	wake_up_interruptible(&rxs->wq);
}
