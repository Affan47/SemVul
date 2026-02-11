usb_amradio_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct amradio_device *radio = to_amradio_dev(usb_get_intfdata(intf));

	mutex_lock(&radio->lock);
	if (!radio->muted) {
		amradio_set_mute(radio, true);
		radio->muted = false;
	}
	mutex_unlock(&radio->lock);

	dev_info(&intf->dev, "going into suspend..\n");
	return 0;
}
