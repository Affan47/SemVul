whc_urb_dequeue(struct usb_hcd *usb_hcd, struct urb *urb, int status)
{
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	struct whc *whc = wusbhc_to_whc(wusbhc);
	int ret;

	switch (usb_pipetype(urb->pipe)) {
	case PIPE_INTERRUPT:
		ret = pzl_urb_dequeue(whc, urb, status);
		break;
	case PIPE_ISOCHRONOUS:
		ret = -ENOTSUPP;
		break;
	case PIPE_CONTROL:
	case PIPE_BULK:
	default:
		ret = asl_urb_dequeue(whc, urb, status);
		break;
	}

	return ret;
}
