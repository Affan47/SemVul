u32 gf_m4a_get_profile(GF_M4ADecSpecInfo *cfg)
{
	switch (cfg->base_object_type) {
	case 2:
		if (cfg->nb_chan <= 2)
			return (cfg->base_sr <= 24000) ? 0x28 : 0x29;
		if (cfg->nb_chan <= 5)
			return (cfg->base_sr <= 48000) ? 0x2A : 0x2B;
		return (cfg->base_sr <= 48000) ? 0x50 : 0x51;
	case 5:
		if (cfg->nb_chan <= 2)
			return (cfg->base_sr <= 24000) ? 0x2C : 0x2D;
		if (cfg->nb_chan <= 5)
			return (cfg->base_sr <= 48000) ? 0x2E : 0x2F;
		return (cfg->base_sr <= 48000) ? 0x52 : 0x53;
	case 29:
		if (cfg->nb_chan <= 2)
			return (cfg->base_sr <= 24000) ? 0x30 : 0x31;
		if (cfg->nb_chan <= 5)
			return (cfg->base_sr <= 48000) ? 0x32 : 0x33;
		return (cfg->base_sr <= 48000) ? 0x54 : 0x55;

	default:
		if (cfg->nb_chan <= 2) return (cfg->base_sr < 24000) ? 0x0E : 0x0F;
		return 0x10;
	}
}
