cx231xx_v4l2_poll(struct file *filp, poll_table *wait)
{
	unsigned long req_events = poll_requested_events(wait);
	struct cx231xx_fh *fh = filp->private_data;
	struct cx231xx *dev = fh->dev;
	unsigned res = 0;
	int rc;

	rc = check_dev(dev);
	if (rc < 0)
		return POLLERR;

	rc = res_get(fh);

	if (unlikely(rc < 0))
		return POLLERR;

	if (v4l2_event_pending(&fh->fh))
		res |= POLLPRI;
	else
		poll_wait(filp, &fh->fh.wait, wait);

	if (!(req_events & (POLLIN | POLLRDNORM)))
		return res;

	if ((V4L2_BUF_TYPE_VIDEO_CAPTURE == fh->type) ||
	    (V4L2_BUF_TYPE_VBI_CAPTURE == fh->type)) {
		mutex_lock(&dev->lock);
		res |= videobuf_poll_stream(filp, &fh->vb_vidq, wait);
		mutex_unlock(&dev->lock);
		return res;
	}
	return res | POLLERR;
}
