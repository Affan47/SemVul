gpio_twl4030_remove(struct platform_device *pdev)
{
	struct twl4030_gpio_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct gpio_twl4030_priv *priv = platform_get_drvdata(pdev);
	int status;

	if (pdata && pdata->teardown) {
		status = pdata->teardown(&pdev->dev, priv->gpio_chip.base,
					 TWL4030_GPIO_MAX);
		if (status) {
			dev_dbg(&pdev->dev, "teardown --> %d\n", status);
			return status;
		}
	}

	gpiochip_remove(&priv->gpio_chip);

	if (is_module())
		return 0;


	WARN_ON(1);
	return -EIO;
}
