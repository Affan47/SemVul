poll_dte(struct sh_mobile_i2c_data *pd)
{
	int i;

	for (i = 1000; i; i--) {
		u_int8_t val = iic_rd(pd, ICSR);

		if (val & ICSR_DTE)
			break;

		if (val & ICSR_TACK)
			return -ENXIO;

		udelay(10);
	}

	return i ? 0 : -ETIMEDOUT;
}
