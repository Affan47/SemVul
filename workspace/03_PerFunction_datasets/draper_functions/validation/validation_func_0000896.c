saa7127_s_vbi_data(struct v4l2_subdev *sd, const struct v4l2_sliced_vbi_data *data)
{
	switch (data->id) {
	case V4L2_SLICED_WSS_625:
		return saa7127_set_wss(sd, data);
	case V4L2_SLICED_VPS:
		return saa7127_set_vps(sd, data);
	case V4L2_SLICED_CAPTION_525:
		if (data->field == 0)
			return saa7127_set_cc(sd, data);
		return saa7127_set_xds(sd, data);
	default:
		return -EINVAL;
	}
	return 0;
}
