scb2_flash_probe(struct pci_dev *dev,
			    const struct pci_device_id *ent)
{
	u8 reg;


	pci_read_config_byte(dev, CSB5_FCR, &reg);
	pci_write_config_byte(dev, CSB5_FCR, reg | CSB5_FCR_DECODE_ALL);

	if (!request_mem_region(SCB2_ADDR, SCB2_WINDOW, scb2_map.name)) {


		printk(KERN_WARNING MODNAME
		    ": warning - can't reserve rom window, continuing\n");
		region_fail = 1;
	}


	scb2_ioaddr = ioremap_nocache(SCB2_ADDR, SCB2_WINDOW);
	if (!scb2_ioaddr) {
		printk(KERN_ERR MODNAME ": Failed to ioremap window!\n");
		if (!region_fail)
			release_mem_region(SCB2_ADDR, SCB2_WINDOW);
		return -ENOMEM;
	}

	scb2_map.phys = SCB2_ADDR;
	scb2_map.virt = scb2_ioaddr;
	scb2_map.size = SCB2_WINDOW;

	simple_map_init(&scb2_map);


	scb2_mtd = do_map_probe("cfi_probe", &scb2_map);

	if (!scb2_mtd) {
		printk(KERN_ERR MODNAME ": flash probe failed!\n");
		iounmap(scb2_ioaddr);
		if (!region_fail)
			release_mem_region(SCB2_ADDR, SCB2_WINDOW);
		return -ENODEV;
	}

	scb2_mtd->owner = THIS_MODULE;
	if (scb2_fixup_mtd(scb2_mtd) < 0) {
		mtd_device_unregister(scb2_mtd);
		map_destroy(scb2_mtd);
		iounmap(scb2_ioaddr);
		if (!region_fail)
			release_mem_region(SCB2_ADDR, SCB2_WINDOW);
		return -ENODEV;
	}

	printk(KERN_NOTICE MODNAME ": chip size 0x%llx at offset 0x%llx\n",
	       (unsigned long long)scb2_mtd->size,
	       (unsigned long long)(SCB2_WINDOW - scb2_mtd->size));

	mtd_device_register(scb2_mtd, NULL, 0);

	return 0;
}
