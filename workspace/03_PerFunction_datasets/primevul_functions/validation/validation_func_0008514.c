static int ov511_i2c_r(struct sd *sd, u8 reg)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int rc, value, retries;


	for (retries = 6; ; ) {

		reg_w(sd, R51x_I2C_SADDR_2, reg);


		reg_w(sd, R511_I2C_CTL, 0x03);

		do {
			rc = reg_r(sd, R511_I2C_CTL);
		} while (rc > 0 && ((rc & 1) == 0));

		if (rc < 0)
			return rc;

		if ((rc & 2) == 0)
			break;


		reg_w(sd, R511_I2C_CTL, 0x10);

		if (--retries < 0) {
			gspca_dbg(gspca_dev, D_USBI, "i2c write retries exhausted\n");
			return -1;
		}
	}


	for (retries = 6; ; ) {

		reg_w(sd, R511_I2C_CTL, 0x05);

		do {
			rc = reg_r(sd, R511_I2C_CTL);
		} while (rc > 0 && ((rc & 1) == 0));

		if (rc < 0)
			return rc;

		if ((rc & 2) == 0)
			break;


		reg_w(sd, R511_I2C_CTL, 0x10);

		if (--retries < 0) {
			gspca_dbg(gspca_dev, D_USBI, "i2c read retries exhausted\n");
			return -1;
		}
	}

	value = reg_r(sd, R51x_I2C_DATA);

	gspca_dbg(gspca_dev, D_USBI, "ov511_i2c_r %02x %02x\n", reg, value);


	reg_w(sd, R511_I2C_CTL, 0x05);

	return value;
}
