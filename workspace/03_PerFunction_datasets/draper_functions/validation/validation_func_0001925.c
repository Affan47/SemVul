rt5677_if1_adc_tdm_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);
	struct rt5677_priv *rt5677 = snd_soc_codec_get_drvdata(codec);
	unsigned int value;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		regmap_read(rt5677->regmap, RT5677_TDM1_CTRL2, &value);
		if (value & RT5677_IF1_ADC_CTRL_MASK)
			regmap_update_bits(rt5677->regmap, RT5677_TDM1_CTRL1,
				RT5677_IF1_ADC_MODE_MASK,
				RT5677_IF1_ADC_MODE_TDM);
		break;

	default:
		return 0;
	}

	return 0;
}
