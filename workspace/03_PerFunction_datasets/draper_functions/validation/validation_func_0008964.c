s5k5baf_i2c_write(struct s5k5baf *state, u16 addr, u16 val)
{
	u8 buf[4] = { addr >> 8, addr & 0xFF, val >> 8, val & 0xFF };
	struct i2c_client *c = v4l2_get_subdevdata(&state->sd);
	int ret;

	if (state->error)
		return;

	ret = i2c_master_send(c, buf, 4);
	v4l2_dbg(3, debug, c, "i2c_write: 0x%04x : 0x%04x\n", addr, val);

	if (ret != 4) {
		v4l2_err(c, "i2c_write: error during transfer (%d)\n", ret);
		state->error = ret;
	}
}
