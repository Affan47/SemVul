void pcan_usb_pro_restart_complete(struct urb *urb)
{

	peak_usb_async_complete(urb);


	peak_usb_restart_complete(urb->context);
}
