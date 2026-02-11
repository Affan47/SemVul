parport_write (struct parport *port, const void *buffer, size_t len)
{
#ifndef CONFIG_PARPORT_1284
	return port->ops->compat_write_data (port, buffer, len, 0);
#else
	ssize_t retval;
	int mode = port->ieee1284.mode;
	int addr = mode & IEEE1284_ADDR;
	size_t (*fn) (struct parport *, const void *, size_t, int);


	mode &= ~(IEEE1284_DEVICEID | IEEE1284_ADDR);


	switch (mode) {
	case IEEE1284_MODE_NIBBLE:
	case IEEE1284_MODE_BYTE:
		parport_negotiate (port, IEEE1284_MODE_COMPAT);
	case IEEE1284_MODE_COMPAT:
		DPRINTK (KERN_DEBUG "%s: Using compatibility mode\n",
			 port->name);
		fn = port->ops->compat_write_data;
		break;

	case IEEE1284_MODE_EPP:
		DPRINTK (KERN_DEBUG "%s: Using EPP mode\n", port->name);
		if (addr) {
			fn = port->ops->epp_write_addr;
		} else {
			fn = port->ops->epp_write_data;
		}
		break;
	case IEEE1284_MODE_EPPSWE:
		DPRINTK (KERN_DEBUG "%s: Using software-emulated EPP mode\n",
			port->name);
		if (addr) {
			fn = parport_ieee1284_epp_write_addr;
		} else {
			fn = parport_ieee1284_epp_write_data;
		}
		break;
	case IEEE1284_MODE_ECP:
	case IEEE1284_MODE_ECPRLE:
		DPRINTK (KERN_DEBUG "%s: Using ECP mode\n", port->name);
		if (addr) {
			fn = port->ops->ecp_write_addr;
		} else {
			fn = port->ops->ecp_write_data;
		}
		break;

	case IEEE1284_MODE_ECPSWE:
		DPRINTK (KERN_DEBUG "%s: Using software-emulated ECP mode\n",
			 port->name);


		if (addr) {
			fn = parport_ieee1284_ecp_write_addr;
		} else {
			fn = parport_ieee1284_ecp_write_data;
		}
		break;

	default:
		DPRINTK (KERN_DEBUG "%s: Unknown mode 0x%02x\n", port->name,
			port->ieee1284.mode);
		return -ENOSYS;
	}

	retval = (*fn) (port, buffer, len, 0);
	DPRINTK (KERN_DEBUG "%s: wrote %d/%d bytes\n", port->name, retval, len);
	return retval;
#endif
}
