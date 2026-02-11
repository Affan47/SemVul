lg216x_set_reg_bit(struct lg216x_state *state,
			      u16 reg, int bit, int onoff)
{
	u8 val;
	int ret;

	lg_reg("reg: 0x%04x, bit: %d, level: %d\n", reg, bit, onoff);

	ret = lg216x_read_reg(state, reg, &val);
	if (lg_fail(ret))
		goto fail;

	val &= ~(1 << bit);
	val |= (onoff & 1) << bit;

	ret = lg216x_write_reg(state, reg, val);
	lg_fail(ret);
fail:
	return ret;
}
