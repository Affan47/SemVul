mv_udc_pullup(struct usb_gadget *gadget, int is_on)
{
	struct mv_udc *udc;
	unsigned long flags;
	int retval = 0;

	udc = container_of(gadget, struct mv_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);

	udc->softconnect = (is_on != 0);

	dev_dbg(&udc->dev->dev, "%s: softconnect %d, vbus_active %d\n",
			__func__, udc->softconnect, udc->vbus_active);

	if (udc->driver && udc->softconnect && udc->vbus_active) {
		retval = mv_udc_enable(udc);
		if (retval == 0) {

			udc_reset(udc);
			ep0_reset(udc);
			udc_start(udc);
		}
	} else if (udc->driver && udc->vbus_active) {

		stop_activity(udc, udc->driver);
		udc_stop(udc);
		mv_udc_disable(udc);
	}

	spin_unlock_irqrestore(&udc->lock, flags);
	return retval;
}
