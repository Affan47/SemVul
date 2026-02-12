static void pcan_usb_fd_exit(struct peak_usb_device *dev)
{
	struct pcan_usb_fd_device *pdev =
			container_of(dev, struct pcan_usb_fd_device, dev);


	if (dev->can.state != CAN_STATE_STOPPED) {

		pcan_usb_fd_set_bus(dev, 0);
	}


	pcan_usb_fd_set_can_led(dev, PCAN_UFD_LED_OFF);


	if (dev->ctrl_idx == 0) {

		if (pdev->usb_if->dev_opened_count > 0)
			pcan_usb_fd_set_options(dev, 0,
						PUCAN_OPTION_ERROR,
						PCAN_UFD_FLTEXT_CALIBRATION);


		pcan_usb_fd_drv_loaded(dev, 0);
	}
}
