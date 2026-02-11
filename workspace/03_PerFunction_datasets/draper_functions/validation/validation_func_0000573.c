stop_streaming(struct vb2_queue *vq)
{
	struct pwc_device *pdev = vb2_get_drv_priv(vq);

	mutex_lock(&pdev->v4l2_lock);
	if (pdev->udev) {
		pwc_set_leds(pdev, 0, 0);
		pwc_camera_power(pdev, 0);
		pwc_isoc_cleanup(pdev);
	}

	pwc_cleanup_queued_bufs(pdev, VB2_BUF_STATE_ERROR);
	if (pdev->fill_buf)
		vb2_buffer_done(&pdev->fill_buf->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	mutex_unlock(&pdev->v4l2_lock);
}
