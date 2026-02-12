static int dwc3_pci_quirks(struct dwc3_pci *dwc)
{
	struct pci_dev			*pdev = dwc->pci;

	if (pdev->vendor == PCI_VENDOR_ID_INTEL) {
		if (pdev->device == PCI_DEVICE_ID_INTEL_BXT ||
				pdev->device == PCI_DEVICE_ID_INTEL_BXT_M) {
			guid_parse(PCI_INTEL_BXT_DSM_GUID, &dwc->guid);
			dwc->has_dsm_for_pm = true;
		}

		if (pdev->device == PCI_DEVICE_ID_INTEL_BYT) {
			struct gpio_desc *gpio;
			int ret;


			ret = dwc3_byt_enable_ulpi_refclock(pdev);
			if (ret)
				return ret;

			ret = devm_acpi_dev_add_driver_gpios(&pdev->dev,
					acpi_dwc3_byt_gpios);
			if (ret)
				dev_dbg(&pdev->dev, "failed to add mapping table\n");


			gpiod_add_lookup_table(&platform_bytcr_gpios);


			gpio = gpiod_get_optional(&pdev->dev, "cs", GPIOD_OUT_LOW);
			if (IS_ERR(gpio))
				return PTR_ERR(gpio);

			gpiod_set_value_cansleep(gpio, 1);
			gpiod_put(gpio);

			gpio = gpiod_get_optional(&pdev->dev, "reset", GPIOD_OUT_LOW);
			if (IS_ERR(gpio))
				return PTR_ERR(gpio);

			if (gpio) {
				gpiod_set_value_cansleep(gpio, 1);
				gpiod_put(gpio);
				usleep_range(10000, 11000);
			}
		}
	}

	return 0;
}
