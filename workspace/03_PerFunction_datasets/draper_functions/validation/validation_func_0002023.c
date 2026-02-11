usb_stor_bulk_transfer_sglist(struct us_data *us, unsigned int pipe,
		struct scatterlist *sg, int num_sg, unsigned int length,
		unsigned int *act_len)
{
	int result;


	if (test_bit(US_FLIDX_ABORTING, &us->dflags))
		return USB_STOR_XFER_ERROR;


	usb_stor_dbg(us, "xfer %u bytes, %d entries\n", length, num_sg);
	result = usb_sg_init(&us->current_sg, us->pusb_dev, pipe, 0,
			sg, num_sg, length, GFP_NOIO);
	if (result) {
		usb_stor_dbg(us, "usb_sg_init returned %d\n", result);
		return USB_STOR_XFER_ERROR;
	}


	set_bit(US_FLIDX_SG_ACTIVE, &us->dflags);


	if (test_bit(US_FLIDX_ABORTING, &us->dflags)) {


		if (test_and_clear_bit(US_FLIDX_SG_ACTIVE, &us->dflags)) {
			usb_stor_dbg(us, "-- cancelling sg request\n");
			usb_sg_cancel(&us->current_sg);
		}
	}


	usb_sg_wait(&us->current_sg);
	clear_bit(US_FLIDX_SG_ACTIVE, &us->dflags);

	result = us->current_sg.status;
	if (act_len)
		*act_len = us->current_sg.bytes;
	return interpret_urb_result(us, pipe, length, result,
			us->current_sg.bytes);
}
