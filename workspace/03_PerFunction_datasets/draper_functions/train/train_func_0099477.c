update_cs43xx_mute(struct oxygen *chip)
{
	u8 reg;

	reg = CS4398_MUTEP_LOW | CS4398_PAMUTE;
	if (chip->dac_mute)
		reg |= CS4398_MUTE_B | CS4398_MUTE_A;
	cs4398_write_cached(chip, 4, reg);
	update_cs4362a_volumes(chip);
}
