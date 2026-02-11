serial_proc_show(struct seq_file *m, void *v)
{
	struct usb_serial *serial;
	struct usb_serial_port *port;
	int i;
	char tmp[40];

	seq_puts(m, "usbserinfo:1.0 driver:2.0\n");
	for (i = 0; i < USB_SERIAL_TTY_MINORS; ++i) {
		port = usb_serial_port_get_by_minor(i);
		if (port == NULL)
			continue;
		serial = port->serial;

		seq_printf(m, "%d:", i);
		if (serial->type->driver.owner)
			seq_printf(m, " module:%s",
				module_name(serial->type->driver.owner));
		seq_printf(m, " name:\"%s\"",
				serial->type->description);
		seq_printf(m, " vendor:%04x product:%04x",
			le16_to_cpu(serial->dev->descriptor.idVendor),
			le16_to_cpu(serial->dev->descriptor.idProduct));
		seq_printf(m, " num_ports:%d", serial->num_ports);
		seq_printf(m, " port:%d", port->port_number);
		usb_make_path(serial->dev, tmp, sizeof(tmp));
		seq_printf(m, " path:%s", tmp);

		seq_putc(m, '\n');
		usb_serial_put(serial);
		mutex_unlock(&serial->disc_mutex);
	}
	return 0;
}
