int v4l_video_std_enumstd(struct v4l2_standard *vs, v4l2_std_id id)
{
	v4l2_std_id curr_id = 0;
	unsigned int index = vs->index, i, j = 0;
	const char *descr = "";


	if (id == 0)
		return -ENODATA;


	for (i = 0; i <= index && id; i++) {


		while ((id & standards[j].std) != standards[j].std)
			j++;
		curr_id = standards[j].std;
		descr = standards[j].descr;
		j++;
		if (curr_id == 0)
			break;
		if (curr_id != V4L2_STD_PAL &&
				curr_id != V4L2_STD_SECAM &&
				curr_id != V4L2_STD_NTSC)
			id &= ~curr_id;
	}
	if (i <= index)
		return -EINVAL;

	v4l2_video_std_construct(vs, curr_id, descr);
	return 0;
}
