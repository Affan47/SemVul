usbhs_interrupt(int irq, void *data)
{
	struct usbhs_priv *priv = data;
	struct usbhs_irq_state irq_state;

	if (usbhs_status_get_each_irq(priv, &irq_state) < 0)
		return IRQ_NONE;


	usbhs_write(priv, INTSTS0, ~irq_state.intsts0 & INTSTS0_MAGIC);
	if (usbhs_mod_is_host(priv))
		usbhs_write(priv, INTSTS1, ~irq_state.intsts1 & INTSTS1_MAGIC);


	if (irq_state.intsts0 & BRDY)
		usbhs_write(priv, BRDYSTS, ~irq_state.brdysts);
	usbhs_write(priv, NRDYSTS, ~irq_state.nrdysts);
	if (irq_state.intsts0 & BEMP)
		usbhs_write(priv, BEMPSTS, ~irq_state.bempsts);


	if (irq_state.intsts0 & VBINT)
		usbhs_mod_info_call(priv, irq_vbus, priv, &irq_state);

	if (irq_state.intsts0 & DVST)
		usbhs_mod_call(priv, irq_dev_state, priv, &irq_state);

	if (irq_state.intsts0 & CTRT)
		usbhs_mod_call(priv, irq_ctrl_stage, priv, &irq_state);

	if (irq_state.intsts0 & BEMP)
		usbhs_mod_call(priv, irq_empty, priv, &irq_state);

	if (irq_state.intsts0 & BRDY)
		usbhs_mod_call(priv, irq_ready, priv, &irq_state);

	if (usbhs_mod_is_host(priv)) {

		if (irq_state.intsts1 & ATTCH)
			usbhs_mod_call(priv, irq_attch, priv, &irq_state);

		if (irq_state.intsts1 & DTCH)
			usbhs_mod_call(priv, irq_dtch, priv, &irq_state);

		if (irq_state.intsts1 & SIGN)
			usbhs_mod_call(priv, irq_sign, priv, &irq_state);

		if (irq_state.intsts1 & SACK)
			usbhs_mod_call(priv, irq_sack, priv, &irq_state);
	}
	return IRQ_HANDLED;
}
