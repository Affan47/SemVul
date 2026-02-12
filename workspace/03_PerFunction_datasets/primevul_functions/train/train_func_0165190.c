static void tda9874a_setmode(struct CHIPSTATE *chip, int mode)
{


	if(tda9874a_mode) {
		if(chip->shadow.bytes[MAXREGS-2] & 0x20)
			tda9874a_NCONR &= 0xfe;
		else
			tda9874a_NCONR |= 0x01;
		chip_write(chip, TDA9874A_NCONR, tda9874a_NCONR);
	}


	if(tda9874a_dic == 0x11) {
		int aosr = 0x80;
		int mdacosr = (tda9874a_mode) ? 0x82:0x80;

		switch(mode) {
		case V4L2_TUNER_MODE_MONO:
		case V4L2_TUNER_MODE_STEREO:
			break;
		case V4L2_TUNER_MODE_LANG1:
			aosr = 0x80;
			mdacosr = (tda9874a_mode) ? 0x82:0x80;
			break;
		case V4L2_TUNER_MODE_LANG2:
			aosr = 0xa0;
			mdacosr = (tda9874a_mode) ? 0x83:0x81;
			break;
		default:
			chip->mode = 0;
			return;
		}
		chip_write(chip, TDA9874A_AOSR, aosr);
		chip_write(chip, TDA9874A_MDACOSR, mdacosr);

		v4l_dbg(1, debug, chip->c, "tda9874a_setmode(): req. mode %d; AOSR=0x%X, MDACOSR=0x%X.\n",
			mode, aosr, mdacosr);

	} else {
		int fmmr,aosr;

		switch(mode) {
		case V4L2_TUNER_MODE_MONO:
			fmmr = 0x00;
			aosr = 0x10;
			break;
		case V4L2_TUNER_MODE_STEREO:
			if(tda9874a_mode) {
				fmmr = 0x00;
				aosr = 0x00;
			} else {
				fmmr = (tda9874a_ESP == 1) ? 0x05 : 0x04;
				aosr = 0x00;
			}
			break;
		case V4L2_TUNER_MODE_LANG1:
			fmmr = 0x02;
			aosr = 0x10;
			break;
		case V4L2_TUNER_MODE_LANG2:
			fmmr = 0x02;
			aosr = 0x20;
			break;
		default:
			chip->mode = 0;
			return;
		}
		chip_write(chip, TDA9874A_FMMR, fmmr);
		chip_write(chip, TDA9874A_AOSR, aosr);

		v4l_dbg(1, debug, chip->c, "tda9874a_setmode(): req. mode %d; FMMR=0x%X, AOSR=0x%X.\n",
			mode, fmmr, aosr);
	}
}
