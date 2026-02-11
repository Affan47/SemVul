mod_init(void)
{
	int err = -ENODEV;
	struct pci_dev *pdev = NULL;
	const struct pci_device_id *ent;
	u32 pmbase;

	for_each_pci_dev(pdev) {
		ent = pci_match_id(pci_tbl, pdev);
		if (ent)
			goto found;
	}

	goto out;

found:
	err = pci_read_config_dword(pdev, 0x58, &pmbase);
	if (err)
		goto out;
	err = -EIO;
	pmbase &= 0x0000FF00;
	if (pmbase == 0)
		goto out;
	if (!request_region(pmbase + 0xF0, 8, "AMD HWRNG")) {
		dev_err(&pdev->dev, "AMD HWRNG region 0x%x already in use!\n",
			pmbase + 0xF0);
		err = -EBUSY;
		goto out;
	}
	amd_rng.priv = (unsigned long)pmbase;
	amd_pdev = pdev;

	pr_info("AMD768 RNG detected\n");
	err = hwrng_register(&amd_rng);
	if (err) {
		pr_err(PFX "RNG registering failed (%d)\n",
		       err);
		release_region(pmbase + 0xF0, 8);
		goto out;
	}
out:
	return err;
}
