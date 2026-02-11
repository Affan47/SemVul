adv76xx_fill_format(struct adv76xx_state *state,
				struct v4l2_mbus_framefmt *format)
{
	memset(format, 0, sizeof(*format));

	format->width = state->timings.bt.width;
	format->height = state->timings.bt.height;
	format->field = V4L2_FIELD_NONE;
	format->colorspace = V4L2_COLORSPACE_SRGB;

	if (state->timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO)
		format->colorspace = (state->timings.bt.height <= 576) ?
			V4L2_COLORSPACE_SMPTE170M : V4L2_COLORSPACE_REC709;
}
