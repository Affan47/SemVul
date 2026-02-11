s2250_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;
	struct s2250 *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (format->pad)
		return -EINVAL;

	if (format->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	if (fmt->height < 640) {
		write_reg_fp(client, 0x12b, state->reg12b_val | 0x400);
		write_reg_fp(client, 0x140, 0x060);
	} else {
		write_reg_fp(client, 0x12b, state->reg12b_val & ~0x400);
		write_reg_fp(client, 0x140, 0x060);
	}
	return 0;
}
