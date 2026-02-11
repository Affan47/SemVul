subdev_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	mask = itv->card->gpio_audio_mode.mask;
	switch (vt->audmode) {
	case V4L2_TUNER_MODE_LANG1:
		data = itv->card->gpio_audio_mode.lang1;
		break;
	case V4L2_TUNER_MODE_LANG2:
		data = itv->card->gpio_audio_mode.lang2;
		break;
	case V4L2_TUNER_MODE_MONO:
		data = itv->card->gpio_audio_mode.mono;
		break;
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1_LANG2:
	default:
		data = itv->card->gpio_audio_mode.stereo;
		break;
	}
	if (mask)
		write_reg((read_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	return 0;
}
