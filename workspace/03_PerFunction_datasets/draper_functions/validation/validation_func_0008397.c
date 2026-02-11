get_coeff(struct snd_soc_codec *codec, int rate)
{
	struct alc5632_priv *alc5632 = snd_soc_codec_get_drvdata(codec);
	int i;

	for (i = 0; i < ARRAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].fs * rate == alc5632->sysclk)
			return i;
	}
	return -EINVAL;
}
