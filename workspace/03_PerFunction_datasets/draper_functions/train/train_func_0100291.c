vidioc_enum_dv_timings(struct file *file, void *_fh,
				    struct v4l2_enum_dv_timings *timings)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);

	if (vdev->vfl_dir == VFL_DIR_RX) {
		if (!vivid_is_hdmi_cap(dev))
			return -ENODATA;
	} else {
		if (!vivid_is_hdmi_out(dev))
			return -ENODATA;
	}
	return v4l2_enum_dv_timings_cap(timings, &vivid_dv_timings_cap,
			NULL, NULL);
}
