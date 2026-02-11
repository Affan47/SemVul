is_up (NMDevice *device)
{
	if (!NM_DEVICE_ETHERNET_GET_PRIVATE (device)->supplicant.mgr)
		return FALSE;

	return TRUE;
}
