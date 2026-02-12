static int tda8425_initialize(struct CHIPSTATE *chip)
{
	struct CHIPDESC *desc = chip->desc;
	int inputmap[4] = {  TDA8425_S1_CH2,  TDA8425_S1_CH1,
			     TDA8425_S1_CH1,  TDA8425_S1_OFF};

	if (chip->c->adapter->id == I2C_HW_B_RIVA) {
		memcpy (desc->inputmap, inputmap, sizeof (inputmap));
	}
	return 0;
}
