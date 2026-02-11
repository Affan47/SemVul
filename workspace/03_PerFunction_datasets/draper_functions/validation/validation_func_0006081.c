rtl8723a_get_fwlps_rf_on(struct rtw_adapter *padapter)
{
	bool retval;
	u32 valRCR;


	if ((padapter->bSurpriseRemoved == true) ||
	    (padapter->pwrctrlpriv.rf_pwrstate == rf_off)) {


		retval = true;
	} else {
		valRCR = rtl8723au_read32(padapter, REG_RCR);
		if (valRCR & 0x00070000)
			retval = false;
		else
			retval = true;
	}

	return retval;
}
