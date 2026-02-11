saa717x_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct saa717x_state *decoder = to_state(sd);
	int dual_f, stereo_f;

	if (decoder->radio)
		return 0;
	get_inf_dev_status(sd, &dual_f, &stereo_f);

	v4l2_dbg(1, debug, sd, "DETECT==st:%d dual:%d\n",
			stereo_f, dual_f);


	if ((dual_f == 0) && (stereo_f == 0)) {
		vt->rxsubchans = V4L2_TUNER_SUB_MONO;
		v4l2_dbg(1, debug, sd, "DETECT==MONO\n");
	}


	if (stereo_f == 1) {
		if (vt->audmode == V4L2_TUNER_MODE_STEREO ||
				vt->audmode == V4L2_TUNER_MODE_LANG1) {
			vt->rxsubchans = V4L2_TUNER_SUB_STEREO;
			v4l2_dbg(1, debug, sd, "DETECT==ST(ST)\n");
		} else {
			vt->rxsubchans = V4L2_TUNER_SUB_MONO;
			v4l2_dbg(1, debug, sd, "DETECT==ST(MONO)\n");
		}
	}


	if (dual_f == 1) {
		if (vt->audmode == V4L2_TUNER_MODE_LANG2) {
			vt->rxsubchans = V4L2_TUNER_SUB_LANG2 | V4L2_TUNER_SUB_MONO;
			v4l2_dbg(1, debug, sd, "DETECT==DUAL1\n");
		} else {
			vt->rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_MONO;
			v4l2_dbg(1, debug, sd, "DETECT==DUAL2\n");
		}
	}
	return 0;
}
