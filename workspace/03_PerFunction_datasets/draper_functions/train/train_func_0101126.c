avma1cs_config(struct pcmcia_device *link)
{
	int i = -1;
	char devname[128];
	IsdnCard_t	icard;
	int busy = 0;

	dev_dbg(&link->dev, "avma1cs_config(0x%p)\n", link);

	devname[0] = 0;
	if (link->prod_id[1])
		strlcpy(devname, link->prod_id[1], sizeof(devname));

	if (pcmcia_loop_config(link, avma1cs_configcheck, NULL))
		return -ENODEV;

	do {


		if (!link->irq) {

			pcmcia_disable_device(link);
			break;
		}


		i = pcmcia_enable_device(link);
		if (i != 0) {
			pcmcia_disable_device(link);
			break;
		}

	} while (0);


	if (i != 0) {
		avma1cs_release(link);
		return -ENODEV;
	}

	icard.para[0] = link->irq;
	icard.para[1] = link->resource[0]->start;
	icard.protocol = isdnprot;
	icard.typ = ISDN_CTYPE_A1_PCMCIA;

	i = hisax_init_pcmcia(link, &busy, &icard);
	if (i < 0) {
		printk(KERN_ERR "avma1_cs: failed to initialize AVM A1 "
		       "PCMCIA %d at i/o %#x\n", i,
		       (unsigned int) link->resource[0]->start);
		avma1cs_release(link);
		return -ENODEV;
	}
	link->priv = (void *) (unsigned long) i;

	return 0;
}
