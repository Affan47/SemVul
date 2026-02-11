advansys_eisa_probe(struct device *dev)
{
	int i, ioport, irq = 0;
	int err;
	struct eisa_device *edev = to_eisa_device(dev);
	struct eisa_scsi_data *data;

	err = -ENOMEM;
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		goto fail;
	ioport = edev->base_addr + 0xc30;

	err = -ENODEV;
	for (i = 0; i < 2; i++, ioport += 0x20) {
		struct asc_board *board;
		struct Scsi_Host *shost;
		if (!request_region(ioport, ASC_IOADR_GAP, DRV_NAME)) {
			printk(KERN_WARNING "Region %x-%x busy\n", ioport,
			       ioport + ASC_IOADR_GAP - 1);
			continue;
		}
		if (!AscFindSignature(ioport)) {
			release_region(ioport, ASC_IOADR_GAP);
			continue;
		}


		inw(ioport + 4);

		if (!irq)
			irq = advansys_eisa_irq_no(edev);

		err = -ENOMEM;
		shost = scsi_host_alloc(&advansys_template, sizeof(*board));
		if (!shost)
			goto release_region;

		board = shost_priv(shost);
		board->irq = irq;
		board->dev = dev;
		board->shost = shost;

		err = advansys_board_found(shost, ioport, ASC_IS_EISA);
		if (!err) {
			data->host[i] = shost;
			continue;
		}

		scsi_host_put(shost);
 release_region:
		release_region(ioport, ASC_IOADR_GAP);
		break;
	}

	if (err)
		goto free_data;
	dev_set_drvdata(dev, data);
	return 0;

 free_data:
	kfree(data->host[0]);
	kfree(data->host[1]);
	kfree(data);
 fail:
	return err;
}
