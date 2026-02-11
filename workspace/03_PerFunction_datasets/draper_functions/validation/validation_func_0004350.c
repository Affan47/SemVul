da9150_gpadc_read_processed(struct da9150_gpadc *gpadc, int channel,
				       int hw_chan, int *val)
{
	int raw_val;

	raw_val = da9150_gpadc_read_adc(gpadc, hw_chan);
	if (raw_val < 0)
		return raw_val;

	switch (channel) {
	case DA9150_GPADC_CHAN_GPIOA:
	case DA9150_GPADC_CHAN_GPIOB:
	case DA9150_GPADC_CHAN_GPIOC:
	case DA9150_GPADC_CHAN_GPIOD:
		*val = da9150_gpadc_gpio_6v_voltage_now(raw_val);
		break;
	case DA9150_GPADC_CHAN_IBUS:
		*val = da9150_gpadc_ibus_current_avg(raw_val);
		break;
	case DA9150_GPADC_CHAN_VBUS:
		*val = da9150_gpadc_vbus_21v_voltage_now(raw_val);
		break;
	case DA9150_GPADC_CHAN_VSYS:
		*val = da9150_gpadc_vsys_6v_voltage_now(raw_val);
		break;
	default:

		*val = raw_val;
		break;
	}

	return IIO_VAL_INT;
}
