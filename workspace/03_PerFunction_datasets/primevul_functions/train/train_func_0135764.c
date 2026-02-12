static UINT serial_irp_request(DEVICE* device, IRP* irp)
{
	SERIAL_DEVICE* serial = (SERIAL_DEVICE*)device;
	assert(irp != NULL);

	if (irp == NULL)
		return CHANNEL_RC_OK;


	if (!MessageQueue_Post(serial->MainIrpQueue, NULL, 0, (void*)irp, NULL))
	{
		WLog_ERR(TAG, "MessageQueue_Post failed!");
		return ERROR_INTERNAL_ERROR;
	}

	return CHANNEL_RC_OK;
}
