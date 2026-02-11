lp55xx_post_init_device(struct lp55xx_chip *chip)
{
	struct lp55xx_device_config *cfg = chip->cfg;

	if (!cfg->post_init_device)
		return 0;

	return cfg->post_init_device(chip);
}
