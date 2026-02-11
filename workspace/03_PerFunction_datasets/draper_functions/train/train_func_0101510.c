as3722_pinctrl_gpio_set_direction(struct pinctrl_dev *pctldev,
		struct pinctrl_gpio_range *range, unsigned offset, bool input)
{
	struct as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	struct as3722 *as3722 = as_pci->as3722;
	int mode;

	mode = as3722_pinctrl_gpio_get_mode(
			as_pci->gpio_control[offset].mode_prop, input);
	if (mode < 0) {
		dev_err(as_pci->dev, "%s direction for GPIO %d not supported\n",
			(input) ? "Input" : "Output", offset);
		return mode;
	}

	return as3722_update_bits(as3722, AS3722_GPIOn_CONTROL_REG(offset),
				AS3722_GPIO_MODE_MASK, mode);
}
