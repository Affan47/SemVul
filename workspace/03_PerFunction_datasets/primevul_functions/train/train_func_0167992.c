static int usbvision_v4l2_open(struct file *file)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	int err_code = 0;

	PDEBUG(DBG_IO, "open");

	if (mutex_lock_interruptible(&usbvision->v4l2_lock))
		return -ERESTARTSYS;

	if (usbvision->user) {
		err_code = -EBUSY;
	} else {
		err_code = v4l2_fh_open(file);
		if (err_code)
			goto unlock;


		err_code = usbvision_scratch_alloc(usbvision);
		if (isoc_mode == ISOC_MODE_COMPRESS) {


			err_code = usbvision_decompress_alloc(usbvision);
		}
		if (err_code) {

			usbvision_scratch_free(usbvision);
			usbvision_decompress_free(usbvision);
		}
	}


	if (!err_code) {

		if (!usbvision->initialized) {
			int setup_ok = 0;
			setup_ok = usbvision_setup(usbvision, isoc_mode);
			if (setup_ok)
				usbvision->initialized = 1;
			else
				err_code = -EBUSY;
		}

		if (!err_code) {
			usbvision_begin_streaming(usbvision);
			err_code = usbvision_init_isoc(usbvision);

			usbvision_muxsel(usbvision, 0);


			usbvision_empty_framequeues(usbvision);
			usbvision->user++;
		}
	}

unlock:
	mutex_unlock(&usbvision->v4l2_lock);

	PDEBUG(DBG_IO, "success");
	return err_code;
}
