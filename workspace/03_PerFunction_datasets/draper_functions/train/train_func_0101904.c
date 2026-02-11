radeon_cp_buffers(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	int ret = 0;
	struct drm_dma *d = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);


	if (d->send_count != 0) {
		DRM_ERROR("Process %d trying to send %d buffers via drmDMA\n",
			  DRM_CURRENTPID, d->send_count);
		return -EINVAL;
	}


	if (d->request_count < 0 || d->request_count > dma->buf_count) {
		DRM_ERROR("Process %d trying to get %d buffers (of %d max)\n",
			  DRM_CURRENTPID, d->request_count, dma->buf_count);
		return -EINVAL;
	}

	d->granted_count = 0;

	if (d->request_count) {
		ret = radeon_cp_get_buffers(dev, file_priv, d);
	}

	return ret;
}
