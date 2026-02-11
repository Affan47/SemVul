HIDDumpTree(hid_dev_handle_t udev, usage_tables_t *utab)
{
	int	i;
#ifndef SHUT_MODE

	int vendorID = usb_device((struct usb_dev_handle *)udev)->descriptor.idVendor;
#endif


	if (nut_debug_level < 1) {
		return;
	}

	for (i = 0; i < pDesc->nitems; i++)
	{
		double		value;
		HIDData_t	*pData = &pDesc->item[i];


#ifdef SHUT_MODE
		if ((pData->ReportID == 254) || (pData->ReportID == 255)) {
			continue;
		}
#else
		if ((vendorID == 0x0463) || (vendorID == 0x047c)) {
			if ((pData->ReportID == 254) || (pData->ReportID == 255)) {
				continue;
			}
		}
#endif


		if (HIDGetDataValue(udev, pData, &value, MAX_TS) == 1) {
			upsdebugx(1, "Path: %s, Type: %s, ReportID: 0x%02x, Offset: %i, Size: %i, Value: %g",
				HIDGetDataItem(pData, utab), HIDDataType(pData), pData->ReportID, pData->Offset, pData->Size, value);
			continue;
		}

		upsdebugx(1, "Path: %s, Type: %s, ReportID: 0x%02x, Offset: %i, Size: %i",
			HIDGetDataItem(pData, utab), HIDDataType(pData), pData->ReportID, pData->Offset, pData->Size);
	}

	fflush(stdout);
}
