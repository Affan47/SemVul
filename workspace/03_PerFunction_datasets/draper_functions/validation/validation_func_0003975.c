xvip_dma_set_format(struct file *file, void *fh, struct v4l2_format *format)
{
	struct v4l2_fh *vfh = file->private_data;
	struct xvip_dma *dma = to_xvip_dma(vfh->vdev);
	const struct xvip_video_format *info;

	__xvip_dma_try_format(dma, &format->fmt.pix, &info);

	if (vb2_is_busy(&dma->queue))
		return -EBUSY;

	dma->format = format->fmt.pix;
	dma->fmtinfo = info;

	return 0;
}
