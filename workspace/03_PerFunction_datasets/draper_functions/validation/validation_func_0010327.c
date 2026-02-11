poll_busy(struct sh_mobile_i2c_data *pd)
{
	int i;

	for (i = 1000; i; i--) {
		u_int8_t val = iic_rd(pd, ICSR);

		dev_dbg(pd->dev, "val 0x%02x pd->sr 0x%02x\n", val, pd->sr);


		if (!(val & ICSR_BUSY)) {

			val |= pd->sr;
			if (val & ICSR_TACK)
				return -ENXIO;
			if (val & ICSR_AL)
				return -EAGAIN;
			break;
		}

		udelay(10);
	}

	return i ? 0 : -ETIMEDOUT;
}
