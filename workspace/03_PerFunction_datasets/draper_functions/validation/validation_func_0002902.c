wm8996_report_headphone(struct snd_soc_codec *codec)
{
	dev_dbg(codec->dev, "Headphone detected\n");
	wm8996_hpdet_start(codec);


	snd_soc_update_bits(codec, WM8996_MIC_DETECT_1,
			    WM8996_MICD_RATE_MASK |
			    WM8996_MICD_BIAS_STARTTIME_MASK,
			    7 << WM8996_MICD_RATE_SHIFT |
			    7 << WM8996_MICD_BIAS_STARTTIME_SHIFT);
}
