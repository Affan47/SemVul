lme2510_int_read(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct lme2510_state *lme_int = adap_to_priv(adap);
	struct usb_host_endpoint *ep;

	lme_int->lme_urb = usb_alloc_urb(0, GFP_ATOMIC);

	if (lme_int->lme_urb == NULL)
			return -ENOMEM;

	lme_int->buffer = usb_alloc_coherent(d->udev, 128, GFP_ATOMIC,
					&lme_int->lme_urb->transfer_dma);

	if (lme_int->buffer == NULL)
			return -ENOMEM;

	usb_fill_int_urb(lme_int->lme_urb,
				d->udev,
				usb_rcvintpipe(d->udev, 0xa),
				lme_int->buffer,
				128,
				lme2510_int_response,
				adap,
				8);


	ep = usb_pipe_endpoint(d->udev, lme_int->lme_urb->pipe);

	if (usb_endpoint_type(&ep->desc) == USB_ENDPOINT_XFER_BULK)
		lme_int->lme_urb->pipe = usb_rcvbulkpipe(d->udev, 0xa),

	lme_int->lme_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_submit_urb(lme_int->lme_urb, GFP_ATOMIC);
	info("INT Interrupt Service Started");

	return 0;
}
