static int stub_recv_cmd_unlink(struct stub_device *sdev,
				struct usbip_header *pdu)
{
	int ret;
	unsigned long flags;
	struct stub_priv *priv;

	spin_lock_irqsave(&sdev->priv_lock, flags);

	list_for_each_entry(priv, &sdev->priv_init, list) {
		if (priv->seqnum != pdu->u.cmd_unlink.seqnum)
			continue;

		dev_info(&priv->urb->dev->dev, "unlink urb %p\n",
			 priv->urb);


		priv->unlinking = 1;


		priv->seqnum = pdu->base.seqnum;

		spin_unlock_irqrestore(&sdev->priv_lock, flags);


		ret = usb_unlink_urb(priv->urb);
		if (ret != -EINPROGRESS)
			dev_err(&priv->urb->dev->dev,
				"failed to unlink a urb %p, ret %d\n",
				priv->urb, ret);

		return 0;
	}

	usbip_dbg_stub_rx("seqnum %d is not pending\n",
			  pdu->u.cmd_unlink.seqnum);


	stub_enqueue_ret_unlink(sdev, pdu->base.seqnum, 0);

	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	return 0;
}
