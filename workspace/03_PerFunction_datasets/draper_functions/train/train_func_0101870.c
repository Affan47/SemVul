sc_create(struct platform_device *pdev)
{
	struct sc_data *sc;

	dev_dbg(&pdev->dev, "sc_create\n");

	sc = devm_kzalloc(&pdev->dev, sizeof(*sc), GFP_KERNEL);
	if (!sc) {
		dev_err(&pdev->dev, "couldn't alloc sc_data\n");
		return ERR_PTR(-ENOMEM);
	}

	sc->pdev = pdev;

	sc->res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "sc");
	if (!sc->res) {
		dev_err(&pdev->dev, "missing platform resources data\n");
		return ERR_PTR(-ENODEV);
	}

	sc->base = devm_ioremap_resource(&pdev->dev, sc->res);
	if (IS_ERR(sc->base)) {
		dev_err(&pdev->dev, "failed to ioremap\n");
		return ERR_CAST(sc->base);
	}

	return sc;
}
