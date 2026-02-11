wm8776_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	struct wm8776_priv *wm8776 = snd_soc_codec_get_drvdata(codec);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_codec_get_bias_level(codec) == SND_SOC_BIAS_OFF) {
			regcache_sync(wm8776->regmap);


			snd_soc_update_bits(codec, WM8776_PWRDOWN, 1, 0);
		}

		break;
	case SND_SOC_BIAS_OFF:
		snd_soc_update_bits(codec, WM8776_PWRDOWN, 1, 1);
		break;
	}

	return 0;
}
