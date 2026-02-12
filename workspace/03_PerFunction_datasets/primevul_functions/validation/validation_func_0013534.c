static int v4l_enumoutput(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	struct v4l2_output *p = arg;


	if (is_valid_ioctl(vfd, VIDIOC_S_STD))
		p->capabilities |= V4L2_OUT_CAP_STD;

	if (vfd->device_caps & V4L2_CAP_IO_MC) {
		if (p->index)
			return -EINVAL;
		strscpy(p->name, vfd->name, sizeof(p->name));
		p->type = V4L2_OUTPUT_TYPE_ANALOG;
		return 0;
	}

	return ops->vidioc_enum_output(file, fh, p);
}
