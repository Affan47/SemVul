static int technisat_usb2_power_ctrl(struct dvb_usb_device *d, int level)
{
	struct technisat_usb2_state *state = d->priv;

	state->power_state = level;

	if (disable_led_control)
		return 0;


	technisat_usb2_set_led(d, 0, TECH_LED_OFF);

	technisat_usb2_set_led(d, 1, TECH_LED_ON);
	return 0;
}
