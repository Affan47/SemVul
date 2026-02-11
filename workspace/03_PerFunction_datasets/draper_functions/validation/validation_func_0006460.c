cs42l73_probe(struct snd_soc_codec *codec)
{
	struct cs42l73_private *cs42l73 = snd_soc_codec_get_drvdata(codec);


	if (cs42l73->pdata.chgfreq)
		snd_soc_update_bits(codec, CS42L73_CPFCHC,
				    CS42L73_CHARGEPUMP_MASK,
					cs42l73->pdata.chgfreq << 4);


	cs42l73->mclksel = CS42L73_CLKID_MCLK1;
	cs42l73->mclk = 0;

	return 0;
}
