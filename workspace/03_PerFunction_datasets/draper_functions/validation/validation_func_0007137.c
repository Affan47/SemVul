wm8960_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
					unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = dai->codec;
	struct wm8960_priv *wm8960 = snd_soc_codec_get_drvdata(codec);

	switch (clk_id) {
	case WM8960_SYSCLK_MCLK:
		snd_soc_update_bits(codec, WM8960_CLOCK1,
					0x1, WM8960_SYSCLK_MCLK);
		break;
	case WM8960_SYSCLK_PLL:
		snd_soc_update_bits(codec, WM8960_CLOCK1,
					0x1, WM8960_SYSCLK_PLL);
		break;
	case WM8960_SYSCLK_AUTO:
		break;
	default:
		return -EINVAL;
	}

	wm8960->sysclk = freq;
	wm8960->clk_id = clk_id;

	return 0;
}
