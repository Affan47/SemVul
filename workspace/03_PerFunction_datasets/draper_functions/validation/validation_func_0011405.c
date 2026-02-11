tlclk_init(void)
{
	int ret;

	ret = register_chrdev(tlclk_major, "telco_clock", &tlclk_fops);
	if (ret < 0) {
		printk(KERN_ERR "tlclk: can't get major %d.\n", tlclk_major);
		return ret;
	}
	tlclk_major = ret;
	alarm_events = kzalloc( sizeof(struct tlclk_alarms), GFP_KERNEL);
	if (!alarm_events) {
		ret = -ENOMEM;
		goto out1;
	}


	if (!request_region(TLCLK_BASE, 8, "telco_clock")) {
		printk(KERN_ERR "tlclk: request_region 0x%X failed.\n",
			TLCLK_BASE);
		ret = -EBUSY;
		goto out2;
	}
	telclk_interrupt = (inb(TLCLK_REG7) & 0x0f);

	if (0x0F == telclk_interrupt ) {
		printk(KERN_ERR "telclk_interrupt = 0x%x non-mcpbl0010 hw.\n",
			telclk_interrupt);
		ret = -ENXIO;
		goto out3;
	}

	init_timer(&switchover_timer);

	ret = misc_register(&tlclk_miscdev);
	if (ret < 0) {
		printk(KERN_ERR "tlclk: misc_register returns %d.\n", ret);
		goto out3;
	}

	tlclk_device = platform_device_register_simple("telco_clock",
				-1, NULL, 0);
	if (IS_ERR(tlclk_device)) {
		printk(KERN_ERR "tlclk: platform_device_register failed.\n");
		ret = PTR_ERR(tlclk_device);
		goto out4;
	}

	ret = sysfs_create_group(&tlclk_device->dev.kobj,
			&tlclk_attribute_group);
	if (ret) {
		printk(KERN_ERR "tlclk: failed to create sysfs device attributes.\n");
		goto out5;
	}

	return 0;
out5:
	platform_device_unregister(tlclk_device);
out4:
	misc_deregister(&tlclk_miscdev);
out3:
	release_region(TLCLK_BASE, 8);
out2:
	kfree(alarm_events);
out1:
	unregister_chrdev(tlclk_major, "telco_clock");
	return ret;
}
