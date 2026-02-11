wm8988_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct wm8988_priv *wm8988 = snd_soc_codec_get_drvdata(codec);
	u16 iface = snd_soc_read(codec, WM8988_IFACE) & 0x1f3;
	u16 srate = snd_soc_read(codec, WM8988_SRATE) & 0x180;
	int coeff;

	coeff = get_coeff(wm8988->sysclk, params_rate(params));
	if (coeff < 0) {
		coeff = get_coeff(wm8988->sysclk / 2, params_rate(params));
		srate |= 0x40;
	}
	if (coeff < 0) {
		dev_err(codec->dev,
			"Unable to configure sample rate %dHz with %dHz MCLK\n",
			params_rate(params), wm8988->sysclk);
		return coeff;
	}


	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		iface |= 0x0004;
		break;
	case 24:
		iface |= 0x0008;
		break;
	case 32:
		iface |= 0x000c;
		break;
	}


	snd_soc_write(codec, WM8988_IFACE, iface);
	if (coeff >= 0)
		snd_soc_write(codec, WM8988_SRATE, srate |
			(coeff_div[coeff].sr << 1) | coeff_div[coeff].usb);

	return 0;
}
