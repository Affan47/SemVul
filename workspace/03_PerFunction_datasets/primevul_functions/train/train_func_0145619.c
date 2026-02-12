static int wpa_set_param(struct net_device *dev, u8 name, u32 value)
{
	uint ret = 0;
	struct adapter *padapter = rtw_netdev_priv(dev);

	switch (name) {
	case IEEE_PARAM_WPA_ENABLED:
		padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_8021X;
		switch (value & 0xff) {
		case 1:
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPAPSK;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			break;
		case 2:
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPA2PSK;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			break;
		}
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
			 ("%s:padapter->securitypriv.ndisauthtype =%d\n", __func__, padapter->securitypriv.ndisauthtype));
		break;
	case IEEE_PARAM_TKIP_COUNTERMEASURES:
		break;
	case IEEE_PARAM_DROP_UNENCRYPTED: {


		break;
	}
	case IEEE_PARAM_PRIVACY_INVOKED:
		break;

	case IEEE_PARAM_AUTH_ALGS:
		ret = wpa_set_auth_algs(dev, value);
		break;
	case IEEE_PARAM_IEEE_802_1X:
		break;
	case IEEE_PARAM_WPAX_SELECT:
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}
	return ret;
}
