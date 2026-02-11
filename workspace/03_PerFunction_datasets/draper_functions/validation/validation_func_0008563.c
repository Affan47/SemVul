noon010_try_frame_size(struct v4l2_mbus_framefmt *mf,
				  const struct noon010_frmsize **size)
{
	unsigned int min_err = ~0;
	int i = ARRAY_SIZE(noon010_sizes);
	const struct noon010_frmsize *fsize = &noon010_sizes[0],
		*match = NULL;

	while (i--) {
		int err = abs(fsize->width - mf->width)
				+ abs(fsize->height - mf->height);

		if (err < min_err) {
			min_err = err;
			match = fsize;
		}
		fsize++;
	}
	if (match) {
		mf->width  = match->width;
		mf->height = match->height;
		if (size)
			*size = match;
		return 0;
	}
	return -EINVAL;
}
