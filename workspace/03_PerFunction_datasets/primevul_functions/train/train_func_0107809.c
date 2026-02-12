static void tweak_special_requests(struct urb *urb)
{
	if (!urb || !urb->setup_packet)
		return;

	if (usb_pipetype(urb->pipe) != PIPE_CONTROL)
		return;

	if (is_clear_halt_cmd(urb))

		 tweak_clear_halt_cmd(urb);

	else if (is_set_interface_cmd(urb))

		tweak_set_interface_cmd(urb);

	else if (is_set_configuration_cmd(urb))

		tweak_set_configuration_cmd(urb);

	else if (is_reset_device_cmd(urb))
		tweak_reset_device_cmd(urb);
	else
		usbip_dbg_stub_rx("no need to tweak\n");
}
