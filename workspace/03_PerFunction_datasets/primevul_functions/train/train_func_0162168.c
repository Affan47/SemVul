static int pcan_usb_fd_start(struct peak_usb_device *dev)
{
	struct pcan_usb_fd_device *pdev =
			container_of(dev, struct pcan_usb_fd_device, dev);
	int err;


	err = pcan_usb_fd_set_filter_std(dev, -1, 0xffffffff);
	if (err)
		return err;


	if (pdev->usb_if->dev_opened_count == 0) {

		peak_usb_init_time_ref(&pdev->usb_if->time_ref,
				       &pcan_usb_pro_fd);


		err = pcan_usb_fd_set_options(dev, 1,
					      PUCAN_OPTION_ERROR,
					      PCAN_UFD_FLTEXT_CALIBRATION);
	}

	pdev->usb_if->dev_opened_count++;


	pdev->bec.txerr = 0;
	pdev->bec.rxerr = 0;

	return err;
}
