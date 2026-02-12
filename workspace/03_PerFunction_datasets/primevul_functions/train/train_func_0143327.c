static void pcan_usb_pro_exit(struct peak_usb_device *dev)
{
	struct pcan_usb_pro_device *pdev =
			container_of(dev, struct pcan_usb_pro_device, dev);


	if (dev->can.state != CAN_STATE_STOPPED) {

		pcan_usb_pro_set_bus(dev, 0);
	}


	if (dev->ctrl_idx == 0) {

		if (pdev->usb_if->dev_opened_count > 0)
			pcan_usb_pro_set_ts(dev, 0);


		pcan_usb_pro_drv_loaded(dev, 0);
	}
}
