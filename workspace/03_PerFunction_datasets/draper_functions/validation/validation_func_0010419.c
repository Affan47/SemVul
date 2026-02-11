saa7134_tvaudio_setinput(struct saa7134_dev *dev,
			      struct saa7134_input *in)
{
	dev->input = in;
	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHILIPS_SAA7130:
	case PCI_DEVICE_ID_PHILIPS_SAA7134:
		mute_input_7134(dev);
		break;
	case PCI_DEVICE_ID_PHILIPS_SAA7133:
	case PCI_DEVICE_ID_PHILIPS_SAA7135:
		mute_input_7133(dev);
		break;
	}
	saa7134_enable_i2s(dev);
}
