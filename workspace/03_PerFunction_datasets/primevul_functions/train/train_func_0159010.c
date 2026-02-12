static int cpia2_s_fmt_vid_cap(struct file *file, void *_fh,
					struct v4l2_format *f)
{
	struct camera_data *cam = video_drvdata(file);
	int err, frame;

	err = cpia2_try_fmt_vid_cap(file, _fh, f);
	if(err != 0)
		return err;

	cam->pixelformat = f->fmt.pix.pixelformat;


	cam->params.compression.inhibit_htables = 0;


	DBG("Requested width = %d, height = %d\n",
	    f->fmt.pix.width, f->fmt.pix.height);
	if (f->fmt.pix.width != cam->width ||
	    f->fmt.pix.height != cam->height) {
		cam->width = f->fmt.pix.width;
		cam->height = f->fmt.pix.height;
		cam->params.roi.width = f->fmt.pix.width;
		cam->params.roi.height = f->fmt.pix.height;
		cpia2_set_format(cam);
	}

	for (frame = 0; frame < cam->num_frames; ++frame) {
		if (cam->buffers[frame].status == FRAME_READING)
			if ((err = sync(cam, frame)) < 0)
				return err;

		cam->buffers[frame].status = FRAME_EMPTY;
	}

	return 0;
}
