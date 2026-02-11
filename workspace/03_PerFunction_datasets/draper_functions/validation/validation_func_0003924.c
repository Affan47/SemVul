adau1761_codec_probe(struct snd_soc_codec *codec)
{
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);
	struct adau1761_platform_data *pdata = codec->dev->platform_data;
	struct adau *adau = snd_soc_codec_get_drvdata(codec);
	int ret;

	ret = adau17x1_add_widgets(codec);
	if (ret < 0)
		return ret;

	if (pdata && pdata->input_differential) {
		regmap_update_bits(adau->regmap, ADAU1761_LEFT_DIFF_INPUT_VOL,
			ADAU1761_DIFF_INPUT_VOL_LDEN,
			ADAU1761_DIFF_INPUT_VOL_LDEN);
		regmap_update_bits(adau->regmap, ADAU1761_RIGHT_DIFF_INPUT_VOL,
			ADAU1761_DIFF_INPUT_VOL_LDEN,
			ADAU1761_DIFF_INPUT_VOL_LDEN);
		ret = snd_soc_add_codec_controls(codec,
			adau1761_differential_mode_controls,
			ARRAY_SIZE(adau1761_differential_mode_controls));
		if (ret)
			return ret;
	} else {
		ret = snd_soc_add_codec_controls(codec,
			adau1761_single_mode_controls,
			ARRAY_SIZE(adau1761_single_mode_controls));
		if (ret)
			return ret;
	}

	switch (adau1761_get_lineout_mode(codec)) {
	case ADAU1761_OUTPUT_MODE_LINE:
		break;
	case ADAU1761_OUTPUT_MODE_HEADPHONE:
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_LINE_LEFT_VOL,
			ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP,
			ADAU1761_PLAY_LINE_LEFT_VOL_MODE_HP);
		regmap_update_bits(adau->regmap, ADAU1761_PLAY_LINE_RIGHT_VOL,
			ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP,
			ADAU1761_PLAY_LINE_RIGHT_VOL_MODE_HP);
		break;
	default:
		return -EINVAL;
	}

	ret = adau1761_setup_headphone_mode(codec);
	if (ret)
		return ret;

	ret = adau1761_setup_digmic_jackdetect(codec);
	if (ret)
		return ret;

	if (adau->type == ADAU1761) {
		ret = snd_soc_dapm_new_controls(dapm, adau1761_dapm_widgets,
			ARRAY_SIZE(adau1761_dapm_widgets));
		if (ret)
			return ret;

		ret = snd_soc_dapm_add_routes(dapm, adau1761_dapm_routes,
			ARRAY_SIZE(adau1761_dapm_routes));
		if (ret)
			return ret;
	}

	ret = adau17x1_add_routes(codec);
	if (ret < 0)
		return ret;

	return 0;
}
