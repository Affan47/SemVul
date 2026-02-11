dwc2_hsotg_ep_disable(struct usb_ep *ep)
{
	struct dwc2_hsotg_ep *hs_ep = our_ep(ep);
	struct dwc2_hsotg *hsotg = hs_ep->parent;
	int dir_in = hs_ep->dir_in;
	int index = hs_ep->index;
	unsigned long flags;
	u32 epctrl_reg;
	u32 ctrl;

	dev_dbg(hsotg->dev, "%s(ep %p)\n", __func__, ep);

	if (ep == &hsotg->eps_out[0]->ep) {
		dev_err(hsotg->dev, "%s: called for ep0\n", __func__);
		return -EINVAL;
	}

	epctrl_reg = dir_in ? DIEPCTL(index) : DOEPCTL(index);

	spin_lock_irqsave(&hsotg->lock, flags);

	hsotg->fifo_map &= ~(1<<hs_ep->fifo_index);
	hs_ep->fifo_index = 0;
	hs_ep->fifo_size = 0;

	ctrl = dwc2_readl(hsotg->regs + epctrl_reg);
	ctrl &= ~DXEPCTL_EPENA;
	ctrl &= ~DXEPCTL_USBACTEP;
	ctrl |= DXEPCTL_SNAK;

	dev_dbg(hsotg->dev, "%s: DxEPCTL=0x%08x\n", __func__, ctrl);
	dwc2_writel(ctrl, hsotg->regs + epctrl_reg);


	dwc2_hsotg_ctrl_epint(hsotg, hs_ep->index, hs_ep->dir_in, 0);


	kill_all_requests(hsotg, hs_ep, -ESHUTDOWN);

	spin_unlock_irqrestore(&hsotg->lock, flags);
	return 0;
}
