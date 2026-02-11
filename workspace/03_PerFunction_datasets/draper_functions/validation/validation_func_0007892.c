cdc_mbim_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct cdc_mbim_state *info = (void *)&dev->data;
	struct cdc_ncm_ctx *ctx = info->ctx;


	if (info->subdriver && info->subdriver->disconnect)
		info->subdriver->disconnect(ctx->control);
	info->subdriver = NULL;


	cdc_ncm_unbind(dev, intf);
}
