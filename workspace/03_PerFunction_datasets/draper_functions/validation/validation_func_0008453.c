adav80x_set_dac_clock(struct snd_soc_codec *codec,
		unsigned int sample_rate)
{
	struct adav80x *adav80x = snd_soc_codec_get_drvdata(codec);
	unsigned int val;

	if (sample_rate <= 48000)
		val = ADAV80X_DAC_CTRL2_DIV1 | ADAV80X_DAC_CTRL2_INTERPOL_256FS;
	else
		val = ADAV80X_DAC_CTRL2_DIV2 | ADAV80X_DAC_CTRL2_INTERPOL_128FS;

	regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL2,
		ADAV80X_DAC_CTRL2_DIV_MASK | ADAV80X_DAC_CTRL2_INTERPOL_MASK,
		val);

	return 0;
}
