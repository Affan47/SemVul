lp8788_adc_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	struct iio_dev *indio_dev;
	struct lp8788_adc *adc;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->lp = lp;
	platform_set_drvdata(pdev, indio_dev);

	indio_dev->dev.of_node = pdev->dev.of_node;
	ret = lp8788_iio_map_register(indio_dev, lp->pdata, adc);
	if (ret)
		return ret;

	mutex_init(&adc->lock);

	indio_dev->dev.parent = &pdev->dev;
	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &lp8788_adc_info;
	indio_dev->channels = lp8788_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(lp8788_adc_channels);

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "iio dev register err: %d\n", ret);
		goto err_iio_device;
	}

	return 0;

err_iio_device:
	iio_map_array_unregister(indio_dev);
	return ret;
}
