dwc2_hsotg_initep(struct dwc2_hsotg *hsotg,
				       struct dwc2_hsotg_ep *hs_ep,
				       int epnum,
				       bool dir_in)
{
	char *dir;

	if (epnum == 0)
		dir = "";
	else if (dir_in)
		dir = "in";
	else
		dir = "out";

	hs_ep->dir_in = dir_in;
	hs_ep->index = epnum;

	snprintf(hs_ep->name, sizeof(hs_ep->name), "ep%d%s", epnum, dir);

	INIT_LIST_HEAD(&hs_ep->queue);
	INIT_LIST_HEAD(&hs_ep->ep.ep_list);


	if (epnum)
		list_add_tail(&hs_ep->ep.ep_list, &hsotg->gadget.ep_list);

	hs_ep->parent = hsotg;
	hs_ep->ep.name = hs_ep->name;
	usb_ep_set_maxpacket_limit(&hs_ep->ep, epnum ? 1024 : EP0_MPS_LIMIT);
	hs_ep->ep.ops = &dwc2_hsotg_ep_ops;

	if (epnum == 0) {
		hs_ep->ep.caps.type_control = true;
	} else {
		hs_ep->ep.caps.type_iso = true;
		hs_ep->ep.caps.type_bulk = true;
		hs_ep->ep.caps.type_int = true;
	}

	if (dir_in)
		hs_ep->ep.caps.dir_in = true;
	else
		hs_ep->ep.caps.dir_out = true;


	if (using_dma(hsotg)) {
		u32 next = DXEPCTL_NEXTEP((epnum + 1) % 15);
		if (dir_in)
			dwc2_writel(next, hsotg->regs + DIEPCTL(epnum));
		else
			dwc2_writel(next, hsotg->regs + DOEPCTL(epnum));
	}
}
