static int sisusb_bulkout_msg(struct sisusb_usb_data *sisusb, int index,
		unsigned int pipe, void *data, int len, int *actual_length,
		int timeout, unsigned int tflags)
{
	struct urb *urb = sisusb->sisurbout[index];
	int retval, byteswritten = 0;


	urb->transfer_flags = 0;

	usb_fill_bulk_urb(urb, sisusb->sisusb_dev, pipe, data, len,
			sisusb_bulk_completeout,
			&sisusb->urbout_context[index]);

	urb->transfer_flags |= tflags;
	urb->actual_length = 0;


	sisusb->urbout_context[index].actual_length = (timeout) ?
			NULL : actual_length;


	sisusb->urbstatus[index] |= SU_URB_BUSY;


	retval = usb_submit_urb(urb, GFP_KERNEL);


	if ((retval == 0) && timeout) {
		wait_event_timeout(sisusb->wait_q,
				(!(sisusb->urbstatus[index] & SU_URB_BUSY)),
				timeout);
		if (sisusb->urbstatus[index] & SU_URB_BUSY) {

			usb_kill_urb(urb);
			retval = -ETIMEDOUT;
		} else {

			retval = urb->status;
			byteswritten = urb->actual_length;
		}
	}

	if (actual_length)
		*actual_length = byteswritten;

	return retval;
}
