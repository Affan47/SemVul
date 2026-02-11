ta8874z_getrxsubchans(struct CHIPSTATE *chip)
{
	int val, mode;

	val = chip_read(chip);
	mode = V4L2_TUNER_SUB_MONO;
	if (val & TA8874Z_B1){
		mode |= V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	}else if (!(val & TA8874Z_B0)){
		mode = V4L2_TUNER_SUB_STEREO;
	}


	return mode;
}
