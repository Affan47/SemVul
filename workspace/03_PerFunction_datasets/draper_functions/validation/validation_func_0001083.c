register_device (int minor, struct pp_struct *pp)
{
	struct parport *port;
	struct pardevice * pdev = NULL;
	char *name;
	int fl;

	name = kasprintf(GFP_KERNEL, CHRDEV "%x", minor);
	if (name == NULL)
		return -ENOMEM;

	port = parport_find_number (minor);
	if (!port) {
		printk (KERN_WARNING "%s: no associated port!\n", name);
		kfree (name);
		return -ENXIO;
	}

	fl = (pp->flags & PP_EXCL) ? PARPORT_FLAG_EXCL : 0;
	pdev = parport_register_device (port, name, NULL,
					NULL, pp_irq, fl, pp);
	parport_put_port (port);

	if (!pdev) {
		printk (KERN_WARNING "%s: failed to register device!\n", name);
		kfree (name);
		return -ENXIO;
	}

	pp->pdev = pdev;
	pr_debug("%s: registered pardevice\n", name);
	return 0;
}
