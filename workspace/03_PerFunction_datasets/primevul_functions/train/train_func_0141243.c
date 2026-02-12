static void ttusb_dec_handle_irq( struct urb *urb)
{
	struct ttusb_dec *dec = urb->context;
	char *buffer = dec->irq_buffer;
	int retval;

	switch(urb->status) {
		case 0:
			break;
		case -ECONNRESET:
		case -ENOENT:
		case -ESHUTDOWN:
		case -ETIME:

			dprintk("%s:urb shutting down with status: %d\n",
					__func__, urb->status);
			return;
		default:
			dprintk("%s:nonzero status received: %d\n",
					__func__,urb->status);
			goto exit;
	}

	if ((buffer[0] == 0x1) && (buffer[2] == 0x15))  {


		if (buffer[4] - 1 < ARRAY_SIZE(rc_keys)) {
			dprintk("%s:rc signal:%d\n", __func__, buffer[4]);
			input_report_key(dec->rc_input_dev, rc_keys[buffer[4] - 1], 1);
			input_sync(dec->rc_input_dev);
			input_report_key(dec->rc_input_dev, rc_keys[buffer[4] - 1], 0);
			input_sync(dec->rc_input_dev);
		}
	}

exit:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval)
		printk("%s - usb_commit_urb failed with result: %d\n",
			__func__, retval);
}
