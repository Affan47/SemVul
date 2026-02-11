keyspan_break_ctl(struct tty_struct *tty, int break_state)
{
	struct usb_serial_port *port = tty->driver_data;
	struct keyspan_port_private 	*p_priv;

	p_priv = usb_get_serial_port_data(port);

	if (break_state == -1)
		p_priv->break_on = 1;
	else
		p_priv->break_on = 0;

	keyspan_send_setup(port, 0);
}
