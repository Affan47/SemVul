set_var(struct fbtft_par *par)
{
	u8 mactrl_data = 0;

	switch (par->info->var.rotate) {
	case 0:
		mactrl_data = 0x08;
		break;
	case 180:
		mactrl_data = 0xC8;
		break;
	case 270:
		mactrl_data = 0xA8;
		break;
	case 90:
		mactrl_data = 0x68;
		break;
	}


	if (par->bgr)
		mactrl_data |= (1 << 2);
	write_reg(par, CMD_MADCTL, mactrl_data);
	write_reg(par, CMD_RAMWR);
	return 0;
}
