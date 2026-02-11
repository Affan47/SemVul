musb_read_setup(struct musb *musb, struct usb_ctrlrequest *req)
{
	struct musb_request	*r;
	void __iomem		*regs = musb->control_ep->regs;

	musb_read_fifo(&musb->endpoints[0], sizeof *req, (u8 *)req);


	dev_dbg(musb->controller, "SETUP req%02x.%02x v%04x i%04x l%d\n",
		req->bRequestType,
		req->bRequest,
		le16_to_cpu(req->wValue),
		le16_to_cpu(req->wIndex),
		le16_to_cpu(req->wLength));


	r = next_ep0_request(musb);
	if (r)
		musb_g_ep0_giveback(musb, &r->request);


	musb->set_address = false;
	musb->ackpend = MUSB_CSR0_P_SVDRXPKTRDY;
	if (req->wLength == 0) {
		if (req->bRequestType & USB_DIR_IN)
			musb->ackpend |= MUSB_CSR0_TXPKTRDY;
		musb->ep0_state = MUSB_EP0_STAGE_ACKWAIT;
	} else if (req->bRequestType & USB_DIR_IN) {
		musb->ep0_state = MUSB_EP0_STAGE_TX;
		musb_writew(regs, MUSB_CSR0, MUSB_CSR0_P_SVDRXPKTRDY);
		while ((musb_readw(regs, MUSB_CSR0)
				& MUSB_CSR0_RXPKTRDY) != 0)
			cpu_relax();
		musb->ackpend = 0;
	} else
		musb->ep0_state = MUSB_EP0_STAGE_RX;
}
