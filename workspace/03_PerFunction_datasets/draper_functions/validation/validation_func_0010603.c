sl811h_stop(struct usb_hcd *hcd)
{
	struct sl811	*sl811 = hcd_to_sl811(hcd);
	unsigned long	flags;

	del_timer_sync(&hcd->rh_timer);

	spin_lock_irqsave(&sl811->lock, flags);
	port_power(sl811, 0);
	spin_unlock_irqrestore(&sl811->lock, flags);
}
