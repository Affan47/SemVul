DCD_EP_PrepareRx( USB_OTG_CORE_HANDLE *pdev,
							 uint8_t   ep_addr,
							 uint8_t *pbuf,
							 uint16_t  buf_len) {
	USB_OTG_EP *ep;

	ep = &pdev->dev.out_ep[ep_addr & 0x7F];


	ep->xfer_buff = pbuf;
	ep->xfer_len = buf_len;
	ep->xfer_count = 0;
	ep->is_in = 0;
	ep->num = ep_addr & 0x7F;

	if (pdev->cfg.dma_enable == 1) {
		ep->dma_addr = (uint32_t)pbuf;
	}

	if ( ep->num == 0 ) {
		USB_OTG_EP0StartXfer(pdev , ep);
	} else {
		USB_OTG_EPStartXfer(pdev, ep );
	}
	return 0;
}
