saa7134_tvaudio_getstereo(struct saa7134_dev *dev)
{
	int retval = V4L2_TUNER_SUB_MONO;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHILIPS_SAA7134:
		if (dev->tvaudio)
			retval = tvaudio_getstereo(dev,dev->tvaudio);
		break;
	case PCI_DEVICE_ID_PHILIPS_SAA7133:
	case PCI_DEVICE_ID_PHILIPS_SAA7135:
		retval = getstereo_7133(dev);
		break;
	}
	return retval;
}
