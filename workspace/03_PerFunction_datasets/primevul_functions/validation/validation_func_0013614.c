static void v4l_sanitize_format(struct v4l2_format *fmt)
{
	unsigned int offset;


	if (fmt->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ||
	    fmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		fmt->fmt.pix_mp.num_planes = min_t(u32, fmt->fmt.pix_mp.num_planes,
					       VIDEO_MAX_PLANES);


	if (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    fmt->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return;

	if (fmt->fmt.pix.priv == V4L2_PIX_FMT_PRIV_MAGIC)
		return;

	fmt->fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;

	offset = offsetof(struct v4l2_pix_format, priv)
	       + sizeof(fmt->fmt.pix.priv);
	memset(((void *)&fmt->fmt.pix) + offset, 0,
	       sizeof(fmt->fmt.pix) - offset);
}
