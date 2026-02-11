vidioc_enum_framesizes(struct file *file, void *priv,
				  struct v4l2_frmsizeenum *fsize)
{
	struct em28xx         *dev = video_drvdata(file);
	struct em28xx_fmt     *fmt;
	unsigned int	      maxw = norm_maxw(dev);
	unsigned int	      maxh = norm_maxh(dev);

	fmt = format_by_fourcc(fsize->pixel_format);
	if (!fmt) {
		em28xx_videodbg("Fourcc format (%08x) invalid.\n",
				fsize->pixel_format);
		return -EINVAL;
	}

	if (dev->board.is_em2800) {
		if (fsize->index > 1)
			return -EINVAL;
		fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		fsize->discrete.width = maxw / (1 + fsize->index);
		fsize->discrete.height = maxh / (1 + fsize->index);
		return 0;
	}

	if (fsize->index != 0)
		return -EINVAL;


	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	scale_to_size(dev, EM28XX_HVSCALE_MAX, EM28XX_HVSCALE_MAX,
		      &fsize->stepwise.min_width, &fsize->stepwise.min_height);
	if (fsize->stepwise.min_width < 48)
		fsize->stepwise.min_width = 48;
	if (fsize->stepwise.min_height < 38)
		fsize->stepwise.min_height = 38;
	fsize->stepwise.max_width = maxw;
	fsize->stepwise.max_height = maxh;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;
	return 0;
}
