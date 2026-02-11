host_start(struct ci_hdrc *ci)
{
	struct usb_hcd *hcd;
	struct ehci_hcd *ehci;
	struct ehci_ci_priv *priv;
	int ret;

	if (usb_disabled())
		return -ENODEV;

	hcd = usb_create_hcd(&ci_ehci_hc_driver, ci->dev, dev_name(ci->dev));
	if (!hcd)
		return -ENOMEM;

	dev_set_drvdata(ci->dev, ci);
	hcd->rsrc_start = ci->hw_bank.phys;
	hcd->rsrc_len = ci->hw_bank.size;
	hcd->regs = ci->hw_bank.abs;
	hcd->has_tt = 1;

	hcd->power_budget = ci->platdata->power_budget;
	hcd->tpl_support = ci->platdata->tpl_support;
	if (ci->phy)
		hcd->phy = ci->phy;
	else
		hcd->usb_phy = ci->usb_phy;

	ehci = hcd_to_ehci(hcd);
	ehci->caps = ci->hw_bank.cap;
	ehci->has_hostpc = ci->hw_bank.lpm;
	ehci->has_tdi_phy_lpm = ci->hw_bank.lpm;
	ehci->imx28_write_fix = ci->imx28_write_fix;

	priv = (struct ehci_ci_priv *)ehci->priv;
	priv->reg_vbus = NULL;

	if (ci->platdata->reg_vbus && !ci_otg_is_fsm_mode(ci)) {
		if (ci->platdata->flags & CI_HDRC_TURN_VBUS_EARLY_ON) {
			ret = regulator_enable(ci->platdata->reg_vbus);
			if (ret) {
				dev_err(ci->dev,
				"Failed to enable vbus regulator, ret=%d\n",
									ret);
				goto put_hcd;
			}
		} else {
			priv->reg_vbus = ci->platdata->reg_vbus;
		}
	}

	ret = usb_add_hcd(hcd, 0, 0);
	if (ret) {
		goto disable_reg;
	} else {
		struct usb_otg *otg = &ci->otg;

		ci->hcd = hcd;

		if (ci_otg_is_fsm_mode(ci)) {
			otg->host = &hcd->self;
			hcd->self.otg_port = 1;
		}
	}

	return ret;

disable_reg:
	if (ci->platdata->reg_vbus && !ci_otg_is_fsm_mode(ci) &&
			(ci->platdata->flags & CI_HDRC_TURN_VBUS_EARLY_ON))
		regulator_disable(ci->platdata->reg_vbus);
put_hcd:
	usb_put_hcd(hcd);

	return ret;
}
