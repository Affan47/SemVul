mixer_read_config(mame_file *f)
{
	struct mixer_config config;

	if (mame_fread(f, config.default_levels, MIXER_MAX_CHANNELS) < MIXER_MAX_CHANNELS ||
	    mame_fread(f, config.mixing_levels, MIXER_MAX_CHANNELS) < MIXER_MAX_CHANNELS)
	{
		memset(config.default_levels, 0xff, sizeof(config.default_levels));
		memset(config.mixing_levels, 0xff, sizeof(config.mixing_levels));
	}

	mixer_load_config(&config);
}
