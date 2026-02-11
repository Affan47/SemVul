lg216x_set_ensemble(struct lg216x_state *state, int id)
{
	int ret;
	u16 reg;
	u8 val;

	switch (state->cfg->lg_chip) {
	case LG2160:
		reg = 0x0400;
		break;
	case LG2161:
	default:
		reg = 0x0500;
		break;
	}

	ret = lg216x_read_reg(state, reg, &val);
	if (lg_fail(ret))
		goto fail;

	val &= 0xfe;
	val |= (id) ? 0x01 : 0x00;

	ret = lg216x_write_reg(state, reg, val);
	lg_fail(ret);
fail:
	return ret;
}
