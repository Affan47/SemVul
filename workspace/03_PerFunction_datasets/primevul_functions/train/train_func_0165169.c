static int tda9874a_setup(struct CHIPSTATE *chip)
{
	chip_write(chip, TDA9874A_AGCGR, 0x00);
	chip_write(chip, TDA9874A_GCONR, tda9874a_GCONR);
	chip_write(chip, TDA9874A_MSR, (tda9874a_mode) ? 0x03:0x02);
	if(tda9874a_dic == 0x11) {
		chip_write(chip, TDA9874A_FMMR, 0x80);
	} else {
		chip_cmd(chip,"tda9874_modelist",&tda9874a_modelist[tda9874a_STD].cmd);
		chip_write(chip, TDA9874A_FMMR, 0x00);
	}
	chip_write(chip, TDA9874A_C1OLAR, 0x00);
	chip_write(chip, TDA9874A_C2OLAR, 0x00);
	chip_write(chip, TDA9874A_NCONR, tda9874a_NCONR);
	chip_write(chip, TDA9874A_NOLAR, 0x00);


	chip_write(chip, TDA9874A_NLELR, 0x14);
	chip_write(chip, TDA9874A_NUELR, 0x50);

	if(tda9874a_dic == 0x11) {
		chip_write(chip, TDA9874A_AMCONR, 0xf9);
		chip_write(chip, TDA9874A_SDACOSR, (tda9874a_mode) ? 0x81:0x80);
		chip_write(chip, TDA9874A_AOSR, 0x80);
		chip_write(chip, TDA9874A_MDACOSR, (tda9874a_mode) ? 0x82:0x80);
		chip_write(chip, TDA9874A_ESP, tda9874a_ESP);
	} else {
		chip_write(chip, TDA9874A_AMCONR, 0xfb);
		chip_write(chip, TDA9874A_SDACOSR, (tda9874a_mode) ? 0x81:0x80);
		chip_write(chip, TDA9874A_AOSR, 0x00);
	}
	v4l_dbg(1, debug, chip->c, "tda9874a_setup(): %s [0x%02X].\n",
		tda9874a_modelist[tda9874a_STD].name,tda9874a_STD);
	return 1;
}
