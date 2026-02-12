static int tda9840_checkit(struct CHIPSTATE *chip)
{
	int rc;
	rc = chip_read(chip);

	return ((rc & 0x1f) == 0) ? 1 : 0;
}
