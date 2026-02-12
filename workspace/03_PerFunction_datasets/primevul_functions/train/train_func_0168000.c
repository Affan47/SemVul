static ssize_t usbvision_read(struct file *file, char __user *buf,
		      size_t count, loff_t *ppos)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	int noblock = file->f_flags & O_NONBLOCK;
	unsigned long lock_flags;
	int ret, i;
	struct usbvision_frame *frame;

	PDEBUG(DBG_IO, "%s: %ld bytes, noblock=%d", __func__,
	       (unsigned long)count, noblock);

	if (!USBVISION_IS_OPERATIONAL(usbvision) || (buf == NULL))
		return -EFAULT;


	if (!usbvision->num_frames) {


		usbvision_frames_free(usbvision);
		usbvision_empty_framequeues(usbvision);
		usbvision_frames_alloc(usbvision, USBVISION_NUMFRAMES);
	}

	if (usbvision->streaming != stream_on) {

		usbvision->streaming = stream_on;
		call_all(usbvision, video, s_stream, 1);
	}


	for (i = 0; i < usbvision->num_frames; i++) {
		frame = &usbvision->frame[i];
		if (frame->grabstate == frame_state_unused) {

			frame->grabstate = frame_state_ready;
			frame->scanstate = scan_state_scanning;

			frame->scanlength = 0;


			frame->v4l2_format = usbvision->palette;

			spin_lock_irqsave(&usbvision->queue_lock, lock_flags);
			list_add_tail(&frame->frame, &usbvision->inqueue);
			spin_unlock_irqrestore(&usbvision->queue_lock,
					       lock_flags);
		}
	}


	if (list_empty(&(usbvision->outqueue))) {
		if (noblock)
			return -EAGAIN;

		ret = wait_event_interruptible
			(usbvision->wait_frame,
			 !list_empty(&(usbvision->outqueue)));
		if (ret)
			return ret;
	}

	spin_lock_irqsave(&usbvision->queue_lock, lock_flags);
	frame = list_entry(usbvision->outqueue.next,
			   struct usbvision_frame, frame);
	list_del(usbvision->outqueue.next);
	spin_unlock_irqrestore(&usbvision->queue_lock, lock_flags);


	if (frame->grabstate == frame_state_error) {
		frame->bytes_read = 0;
		return 0;
	}

	PDEBUG(DBG_IO, "%s: frmx=%d, bytes_read=%ld, scanlength=%ld",
	       __func__,
	       frame->index, frame->bytes_read, frame->scanlength);


	if ((count + frame->bytes_read) > (unsigned long)frame->scanlength)
		count = frame->scanlength - frame->bytes_read;

	if (copy_to_user(buf, frame->data + frame->bytes_read, count))
		return -EFAULT;

	frame->bytes_read += count;
	PDEBUG(DBG_IO, "%s: {copy} count used=%ld, new bytes_read=%ld",
	       __func__,
	       (unsigned long)count, frame->bytes_read);

#if 1


	frame->bytes_read = 0;


	frame->grabstate = frame_state_unused;
#else
	if (frame->bytes_read >= frame->scanlength) {

		frame->bytes_read = 0;


		frame->grabstate = frame_state_unused;
	}
#endif

	return count;
}
