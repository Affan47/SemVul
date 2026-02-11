dwc2_restore_global_registers(struct dwc2_hsotg *hsotg)
{
	struct dwc2_gregs_backup *gr;
	int i;

	dev_dbg(hsotg->dev, "%s\n", __func__);


	gr = &hsotg->gr_backup;
	if (!gr->valid) {
		dev_err(hsotg->dev, "%s: no global registers to restore\n",
				__func__);
		return -EINVAL;
	}
	gr->valid = false;

	dwc2_writel(0xffffffff, hsotg->regs + GINTSTS);
	dwc2_writel(gr->gotgctl, hsotg->regs + GOTGCTL);
	dwc2_writel(gr->gintmsk, hsotg->regs + GINTMSK);
	dwc2_writel(gr->gusbcfg, hsotg->regs + GUSBCFG);
	dwc2_writel(gr->gahbcfg, hsotg->regs + GAHBCFG);
	dwc2_writel(gr->grxfsiz, hsotg->regs + GRXFSIZ);
	dwc2_writel(gr->gnptxfsiz, hsotg->regs + GNPTXFSIZ);
	dwc2_writel(gr->hptxfsiz, hsotg->regs + HPTXFSIZ);
	dwc2_writel(gr->gdfifocfg, hsotg->regs + GDFIFOCFG);
	for (i = 0; i < MAX_EPS_CHANNELS; i++)
		dwc2_writel(gr->dtxfsiz[i], hsotg->regs + DPTXFSIZN(i));

	return 0;
}
