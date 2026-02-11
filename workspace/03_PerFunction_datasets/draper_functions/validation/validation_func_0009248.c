USBSetConfiguration(U8 bConfigIndex, U8 bAltSetting)
{
	const U8 *pab;
	U8	bCurConfig, bCurAltSetting;
	U8	bEP;
	U16	wMaxPktSize;

	ASSERT(pabDescrip != NULL);

	if (bConfigIndex == 0) {

		USBHwConfigDevice(FALSE);
	}
	else {

		pab = (const U8 *)pabDescrip;
		bCurConfig = 0xFF;
		bCurAltSetting = 0xFF;

		while (pab[DESC_bLength] != 0) {

			switch (pab[DESC_bDescriptorType]) {

			case DESC_CONFIGURATION:

				bCurConfig = pab[CONF_DESC_bConfigurationValue];
				break;

			case DESC_INTERFACE:

				bCurAltSetting = pab[INTF_DESC_bAlternateSetting];
				break;

			case DESC_ENDPOINT:
				if ((bCurConfig == bConfigIndex) &&
					(bCurAltSetting == bAltSetting)) {

					bEP = pab[ENDP_DESC_bEndpointAddress];
					wMaxPktSize = 	(pab[ENDP_DESC_wMaxPacketSize]) |
									(pab[ENDP_DESC_wMaxPacketSize + 1] << 8);

					USBHwEPConfig(bEP, wMaxPktSize);
				}
				break;

			default:
				break;
			}

			pab += pab[DESC_bLength];
		}


		USBHwConfigDevice(TRUE);
	}

	return TRUE;
}
