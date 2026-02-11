lan78xx_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct lan78xx_net *dev = usb_get_intfdata(intf);
	struct lan78xx_priv *pdata = (struct lan78xx_priv *)(dev->data[0]);
	u32 buf;
	int ret;
	int event;

	event = message.event;

	if (!dev->suspend_count++) {
		spin_lock_irq(&dev->txq.lock);

		if ((skb_queue_len(&dev->txq) ||
		     skb_queue_len(&dev->txq_pend)) &&
			PMSG_IS_AUTO(message)) {
			spin_unlock_irq(&dev->txq.lock);
			ret = -EBUSY;
			goto out;
		} else {
			set_bit(EVENT_DEV_ASLEEP, &dev->flags);
			spin_unlock_irq(&dev->txq.lock);
		}


		ret = lan78xx_read_reg(dev, MAC_TX, &buf);
		buf &= ~MAC_TX_TXEN_;
		ret = lan78xx_write_reg(dev, MAC_TX, buf);
		ret = lan78xx_read_reg(dev, MAC_RX, &buf);
		buf &= ~MAC_RX_RXEN_;
		ret = lan78xx_write_reg(dev, MAC_RX, buf);


		netif_device_detach(dev->net);
		lan78xx_terminate_urbs(dev);
		usb_kill_urb(dev->urb_intr);


		netif_device_attach(dev->net);
	}

	if (test_bit(EVENT_DEV_ASLEEP, &dev->flags)) {
		if (PMSG_IS_AUTO(message)) {

			ret = lan78xx_read_reg(dev, MAC_TX, &buf);
			buf &= ~MAC_TX_TXEN_;
			ret = lan78xx_write_reg(dev, MAC_TX, buf);
			ret = lan78xx_read_reg(dev, MAC_RX, &buf);
			buf &= ~MAC_RX_RXEN_;
			ret = lan78xx_write_reg(dev, MAC_RX, buf);

			ret = lan78xx_write_reg(dev, WUCSR, 0);
			ret = lan78xx_write_reg(dev, WUCSR2, 0);
			ret = lan78xx_write_reg(dev, WK_SRC, 0xFFF1FF1FUL);


			ret = lan78xx_read_reg(dev, WUCSR, &buf);

			buf |= WUCSR_RFE_WAKE_EN_;
			buf |= WUCSR_STORE_WAKE_;

			ret = lan78xx_write_reg(dev, WUCSR, buf);

			ret = lan78xx_read_reg(dev, PMT_CTL, &buf);

			buf &= ~PMT_CTL_RES_CLR_WKP_EN_;
			buf |= PMT_CTL_RES_CLR_WKP_STS_;

			buf |= PMT_CTL_PHY_WAKE_EN_;
			buf |= PMT_CTL_WOL_EN_;
			buf &= ~PMT_CTL_SUS_MODE_MASK_;
			buf |= PMT_CTL_SUS_MODE_3_;

			ret = lan78xx_write_reg(dev, PMT_CTL, buf);

			ret = lan78xx_read_reg(dev, PMT_CTL, &buf);

			buf |= PMT_CTL_WUPS_MASK_;

			ret = lan78xx_write_reg(dev, PMT_CTL, buf);

			ret = lan78xx_read_reg(dev, MAC_RX, &buf);
			buf |= MAC_RX_RXEN_;
			ret = lan78xx_write_reg(dev, MAC_RX, buf);
		} else {
			lan78xx_set_suspend(dev, pdata->wol);
		}
	}

	ret = 0;
out:
	return ret;
}
