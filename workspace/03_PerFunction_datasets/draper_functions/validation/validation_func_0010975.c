brightness_set(unsigned int value)
{
	int res;

	if (value > bright_maxlvl)
		return -EINVAL;

	vdbg_printk(TPACPI_DBG_BRGHT,
			"set backlight level to %d\n", value);

	res = mutex_lock_killable(&brightness_mutex);
	if (res < 0)
		return res;

	switch (brightness_mode) {
	case TPACPI_BRGHT_MODE_EC:
	case TPACPI_BRGHT_MODE_ECNVRAM:
		res = tpacpi_brightness_set_ec(value);
		break;
	case TPACPI_BRGHT_MODE_UCMS_STEP:
		res = tpacpi_brightness_set_ucmsstep(value);
		break;
	default:
		res = -ENXIO;
	}

	mutex_unlock(&brightness_mutex);
	return res;
}
