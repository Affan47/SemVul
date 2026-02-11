init_atmel(void)
{
	int rc = 0;
	void __iomem *iobase = NULL;
	int have_region, region_size;
	unsigned long base;
	struct  tpm_chip *chip;

	rc = platform_driver_register(&atml_drv);
	if (rc)
		return rc;

	if ((iobase = atmel_get_base_addr(&base, &region_size)) == NULL) {
		rc = -ENODEV;
		goto err_unreg_drv;
	}

	have_region =
	    (atmel_request_region
	     (base, region_size, "tpm_atmel0") == NULL) ? 0 : 1;

	pdev = platform_device_register_simple("tpm_atmel", -1, NULL, 0);
	if (IS_ERR(pdev)) {
		rc = PTR_ERR(pdev);
		goto err_rel_reg;
	}

	chip = tpmm_chip_alloc(&pdev->dev, &tpm_atmel);
	if (IS_ERR(chip)) {
		rc = PTR_ERR(chip);
		goto err_unreg_dev;
	}

	chip->vendor.iobase = iobase;
	chip->vendor.base = base;
	chip->vendor.have_region = have_region;
	chip->vendor.region_size = region_size;

	rc = tpm_chip_register(chip);
	if (rc)
		goto err_unreg_dev;

	return 0;

err_unreg_dev:
	platform_device_unregister(pdev);
err_rel_reg:
	atmel_put_base_addr(iobase);
	if (have_region)
		atmel_release_region(base,
				     region_size);
err_unreg_drv:
	platform_driver_unregister(&atml_drv);
	return rc;
}
