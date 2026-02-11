setbrightness(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_OV767x) {
		if (val < 0)
			val = 0x80 - val;
		sccb_reg_write(gspca_dev, 0x55, val);
	} else {
		sccb_reg_write(gspca_dev, 0x9b, val);
	}
}
