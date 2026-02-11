saa7164_get_descriptors(struct saa7164_dev *dev)
{
	memcpy_fromio(&dev->hwdesc, dev->bmmio, sizeof(struct tmComResHWDescr));
	memcpy_fromio(&dev->intfdesc, dev->bmmio + sizeof(struct tmComResHWDescr),
		sizeof(struct tmComResInterfaceDescr));
	memcpy_fromio(&dev->busdesc, dev->bmmio + dev->intfdesc.BARLocation,
		sizeof(struct tmComResBusDescr));

	if (dev->hwdesc.bLength != sizeof(struct tmComResHWDescr)) {
		printk(KERN_ERR "Structure struct tmComResHWDescr is mangled\n");
		printk(KERN_ERR "Need %x got %d\n", dev->hwdesc.bLength,
			(u32)sizeof(struct tmComResHWDescr));
	} else
		saa7164_dump_hwdesc(dev);

	if (dev->intfdesc.bLength != sizeof(struct tmComResInterfaceDescr)) {
		printk(KERN_ERR "struct struct tmComResInterfaceDescr is mangled\n");
		printk(KERN_ERR "Need %x got %d\n", dev->intfdesc.bLength,
			(u32)sizeof(struct tmComResInterfaceDescr));
	} else
		saa7164_dump_intfdesc(dev);

	saa7164_dump_busdesc(dev);
}
