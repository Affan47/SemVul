s5k4aa_set_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	int err;

	PDEBUG(D_CONF, "Set gain to %d", val);
	err = m5602_write_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (err < 0)
		return err;

	data = val & 0xff;
	err = m5602_write_sensor(sd, S5K4AA_GAIN, &data, 1);

	return err;
}
