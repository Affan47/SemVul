msp430_ir_init(struct budget_ci *budget_ci)
{
	struct saa7146_dev *saa = budget_ci->budget.dev;
	struct rc_dev *dev;
	int error;

	dev = rc_allocate_device();
	if (!dev) {
		printk(KERN_ERR "budget_ci: IR interface initialisation failed\n");
		return -ENOMEM;
	}

	snprintf(budget_ci->ir.name, sizeof(budget_ci->ir.name),
		 "Budget-CI dvb ir receiver %s", saa->name);
	snprintf(budget_ci->ir.phys, sizeof(budget_ci->ir.phys),
		 "pci-%s/ir0", pci_name(saa->pci));

	dev->driver_name = MODULE_NAME;
	dev->input_name = budget_ci->ir.name;
	dev->input_phys = budget_ci->ir.phys;
	dev->input_id.bustype = BUS_PCI;
	dev->input_id.version = 1;
	if (saa->pci->subsystem_vendor) {
		dev->input_id.vendor = saa->pci->subsystem_vendor;
		dev->input_id.product = saa->pci->subsystem_device;
	} else {
		dev->input_id.vendor = saa->pci->vendor;
		dev->input_id.product = saa->pci->device;
	}
	dev->dev.parent = &saa->pci->dev;

	if (rc5_device < 0)
		budget_ci->ir.rc5_device = IR_DEVICE_ANY;
	else
		budget_ci->ir.rc5_device = rc5_device;


	switch (budget_ci->budget.dev->pci->subsystem_device) {
	case 0x100c:
	case 0x100f:
	case 0x1011:
	case 0x1012:

		dev->map_name = RC_MAP_HAUPPAUGE;
		budget_ci->ir.full_rc5 = true;

		if (rc5_device < 0)
			budget_ci->ir.rc5_device = 0x1f;
		break;
	case 0x1010:
	case 0x1017:
	case 0x1019:
	case 0x101a:
	case 0x101b:

		dev->map_name = RC_MAP_TT_1500;
		break;
	default:

		dev->map_name = RC_MAP_BUDGET_CI_OLD;
		break;
	}
	if (!budget_ci->ir.full_rc5)
		dev->scancode_mask = 0xff;

	error = rc_register_device(dev);
	if (error) {
		printk(KERN_ERR "budget_ci: could not init driver for IR device (code %d)\n", error);
		rc_free_device(dev);
		return error;
	}

	budget_ci->ir.dev = dev;

	tasklet_init(&budget_ci->ir.msp430_irq_tasklet, msp430_ir_interrupt,
		     (unsigned long) budget_ci);

	SAA7146_IER_ENABLE(saa, MASK_06);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_IRQHI);

	return 0;
}
