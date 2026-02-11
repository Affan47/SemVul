twl4030_kpread(struct twl4030_keypad *kp,
		u8 *data, u32 reg, u8 num_bytes)
{
	int ret = twl_i2c_read(TWL4030_MODULE_KEYPAD, data, reg, num_bytes);

	if (ret < 0)
		dev_warn(kp->dbg_dev,
			"Couldn't read TWL4030: %X - ret %d[%x]\n",
			 reg, ret, ret);

	return ret;
}
