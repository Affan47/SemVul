ov7670_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct ov7670_format_struct *ovfmt;
	struct ov7670_win_size *wsize;
	struct ov7670_info *info = to_state(sd);
	unsigned char com7;
	int ret;

	if (format->pad)
		return -EINVAL;

	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
		ret = ov7670_try_fmt_internal(sd, &format->format, NULL, NULL);
		if (ret)
			return ret;
		cfg->try_fmt = format->format;
		return 0;
	}

	ret = ov7670_try_fmt_internal(sd, &format->format, &ovfmt, &wsize);

	if (ret)
		return ret;


	com7 = ovfmt->regs[0].value;
	com7 |= wsize->com7_bit;
	ov7670_write(sd, REG_COM7, com7);


	ov7670_write_array(sd, ovfmt->regs + 1);
	ov7670_set_hw(sd, wsize->hstart, wsize->hstop, wsize->vstart,
			wsize->vstop);
	ret = 0;
	if (wsize->regs)
		ret = ov7670_write_array(sd, wsize->regs);
	info->fmt = ovfmt;


	if (ret == 0)
		ret = ov7670_write(sd, REG_CLKRC, info->clkrc);
	return 0;
}
