static int vidioc_g_parm(struct file *file, void *priv,
			 struct v4l2_streamparm *parm)
{


	struct v4l2_loopback_device *dev;
	MARK();

	dev = v4l2loopback_getdevice(file);
	parm->parm.capture = dev->capture_param;
	return 0;
}
