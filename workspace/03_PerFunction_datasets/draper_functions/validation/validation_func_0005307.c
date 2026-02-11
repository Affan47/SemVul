usbhsg_recip_handler_std_get_endpoint(struct usbhs_priv *priv,
						 struct usbhsg_uep *uep,
						 struct usb_ctrlrequest *ctrl)
{
	struct usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	struct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);
	unsigned short status = 0;

	if (usbhs_pipe_is_stall(pipe))
		status = 1 << USB_ENDPOINT_HALT;

	__usbhsg_recip_send_status(gpriv, status);

	return 0;
}
