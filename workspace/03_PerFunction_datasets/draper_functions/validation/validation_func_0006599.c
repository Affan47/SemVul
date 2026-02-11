ufx_disable(struct ufx_data *dev, bool wait)
{
	u32 dc_ctrl, dc_sts;
	int i;

	int status = ufx_reg_read(dev, 0x2004, &dc_sts);
	check_warn_return(status, "ufx_disable error reading 0x2004");

	status = ufx_reg_read(dev, 0x2000, &dc_ctrl);
	check_warn_return(status, "ufx_disable error reading 0x2000");


	if (((dc_sts & 0x00000001) == 0) || ((dc_ctrl & 0x00000001) == 0))
		return 0;


	dc_ctrl &= ~(0x00000001);
	status = ufx_reg_write(dev, 0x2000, dc_ctrl);
	check_warn_return(status, "ufx_disable error writing 0x2000");


	if (!wait)
		return 0;

	for (i = 0; i < 250; i++) {
		status = ufx_reg_read(dev, 0x2004, &dc_sts);
		check_warn_return(status, "ufx_disable error reading 0x2004");

		if ((dc_sts & 0x00000001) == 0)
			return 0;
	}


	return -EIO;
}
