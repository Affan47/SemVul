snd_caiaq_input_read_analog(struct snd_usb_caiaqdev *cdev,
					const unsigned char *buf,
					unsigned int len)
{
	struct input_dev *input_dev = cdev->input_dev;

	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL2):
		snd_caiaq_input_report_abs(cdev, ABS_X, buf, 2);
		snd_caiaq_input_report_abs(cdev, ABS_Y, buf, 0);
		snd_caiaq_input_report_abs(cdev, ABS_Z, buf, 1);
		break;
	case USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL3):
	case USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER):
	case USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER2):
		snd_caiaq_input_report_abs(cdev, ABS_X, buf, 0);
		snd_caiaq_input_report_abs(cdev, ABS_Y, buf, 1);
		snd_caiaq_input_report_abs(cdev, ABS_Z, buf, 2);
		break;
	case USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
		snd_caiaq_input_report_abs(cdev, ABS_HAT0X, buf, 4);
		snd_caiaq_input_report_abs(cdev, ABS_HAT0Y, buf, 2);
		snd_caiaq_input_report_abs(cdev, ABS_HAT1X, buf, 6);
		snd_caiaq_input_report_abs(cdev, ABS_HAT1Y, buf, 1);
		snd_caiaq_input_report_abs(cdev, ABS_HAT2X, buf, 7);
		snd_caiaq_input_report_abs(cdev, ABS_HAT2Y, buf, 0);
		snd_caiaq_input_report_abs(cdev, ABS_HAT3X, buf, 5);
		snd_caiaq_input_report_abs(cdev, ABS_HAT3Y, buf, 3);
		break;
	}

	input_sync(input_dev);
}
