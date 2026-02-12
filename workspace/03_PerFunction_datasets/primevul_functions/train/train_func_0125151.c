bool snd_usb_get_sample_rate_quirk(struct snd_usb_audio *chip)
{

	switch (chip->usb_id) {
	case USB_ID(0x045E, 0x075D):
	case USB_ID(0x045E, 0x076D):
	case USB_ID(0x045E, 0x076E):
	case USB_ID(0x045E, 0x076F):
	case USB_ID(0x045E, 0x0772):
	case USB_ID(0x045E, 0x0779):
	case USB_ID(0x047F, 0xAA05):
	case USB_ID(0x04D8, 0xFEEA):
	case USB_ID(0x074D, 0x3553):
	case USB_ID(0x21B4, 0x0081):
		return true;
	}
	return false;
}
