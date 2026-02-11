pdacf_pcm_clear_sram(struct snd_pdacf *chip)
{
	int max_loop = 64 * 1024;

	while (inw(chip->port + PDAUDIOCF_REG_RDP) != inw(chip->port + PDAUDIOCF_REG_WDP)) {
		if (max_loop-- < 0)
			return -EIO;
		inw(chip->port + PDAUDIOCF_REG_MD);
	}
	return 0;
}
