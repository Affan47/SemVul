usbhsg_gadget_stop(struct usb_gadget *gadget)
{
	struct usbhsg_gpriv *gpriv = usbhsg_gadget_to_gpriv(gadget);
	struct usbhs_priv *priv = usbhsg_gpriv_to_priv(gpriv);

	usbhsg_try_stop(priv, USBHSG_STATUS_REGISTERD);

	if (!IS_ERR_OR_NULL(gpriv->transceiver))
		otg_set_peripheral(gpriv->transceiver->otg, NULL);

	gpriv->driver = NULL;

	return 0;
}
