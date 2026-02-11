can_interrupt_activation (NMDevice *dev)
{
	NMDeviceAdsl *self = NM_DEVICE_ADSL (dev);
	gboolean interrupt = FALSE;


	if (NM_DEVICE_ADSL_GET_PRIVATE (self)->carrier == FALSE)
		interrupt = TRUE;

	return interrupt;
}
