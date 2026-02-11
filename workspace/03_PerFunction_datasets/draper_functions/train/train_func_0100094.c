snd_hdac_power_up_pm(struct hdac_device *codec)
{
	if (!atomic_inc_not_zero(&codec->in_pm))
		return snd_hdac_power_up(codec);
	return 0;
}
