rt5670_set_bias_level(struct snd_soc_codec *codec,
			enum snd_soc_bias_level level)
{
	struct rt5670_priv *rt5670 = snd_soc_codec_get_drvdata(codec);

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (SND_SOC_BIAS_STANDBY == snd_soc_codec_get_bias_level(codec)) {
			snd_soc_update_bits(codec, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2);
			mdelay(10);
			snd_soc_update_bits(codec, RT5670_PWR_ANLG1,
				RT5670_PWR_FV1 | RT5670_PWR_FV2,
				RT5670_PWR_FV1 | RT5670_PWR_FV2);
			snd_soc_update_bits(codec, RT5670_CHARGE_PUMP,
				RT5670_OSW_L_MASK | RT5670_OSW_R_MASK,
				RT5670_OSW_L_DIS | RT5670_OSW_R_DIS);
			snd_soc_update_bits(codec, RT5670_DIG_MISC, 0x1, 0x1);
			snd_soc_update_bits(codec, RT5670_PWR_ANLG1,
				RT5670_LDO_SEL_MASK, 0x3);
		}
		break;
	case SND_SOC_BIAS_STANDBY:
		snd_soc_update_bits(codec, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2, 0);
		snd_soc_update_bits(codec, RT5670_PWR_ANLG1,
				RT5670_LDO_SEL_MASK, 0x1);
		break;
	case SND_SOC_BIAS_OFF:
		if (rt5670->pdata.jd_mode)
			snd_soc_update_bits(codec, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2,
				RT5670_PWR_MB | RT5670_PWR_BG);
		else
			snd_soc_update_bits(codec, RT5670_PWR_ANLG1,
				RT5670_PWR_VREF1 | RT5670_PWR_MB |
				RT5670_PWR_BG | RT5670_PWR_VREF2 |
				RT5670_PWR_FV1 | RT5670_PWR_FV2, 0);

		snd_soc_update_bits(codec, RT5670_DIG_MISC, 0x1, 0x0);
		break;

	default:
		break;
	}

	return 0;
}
