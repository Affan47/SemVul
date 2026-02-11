snd_atiixp_aclink_reset(struct atiixp *chip)
{
	int timeout;


	if (atiixp_update(chip, CMD, ATI_REG_CMD_POWERDOWN, 0))
		udelay(10);


	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SOFT_RESET, ATI_REG_CMD_AC_SOFT_RESET);
	atiixp_read(chip, CMD);
	udelay(10);
	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SOFT_RESET, 0);

	timeout = 10;
	while (! (atiixp_read(chip, CMD) & ATI_REG_CMD_ACLINK_ACTIVE)) {

		atiixp_update(chip, CMD, ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET,
			      ATI_REG_CMD_AC_SYNC);
		atiixp_read(chip, CMD);
		mdelay(1);
		atiixp_update(chip, CMD, ATI_REG_CMD_AC_RESET, ATI_REG_CMD_AC_RESET);
		if (!--timeout) {
			dev_err(chip->card->dev, "codec reset timeout\n");
			break;
		}
	}


	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET,
		      ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET);

	return 0;
}
