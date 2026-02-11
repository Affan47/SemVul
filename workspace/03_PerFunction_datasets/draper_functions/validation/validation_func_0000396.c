rtw_is_desired_network(struct adapter *adapter, struct wlan_network *pnetwork)
{
	struct security_priv *psecuritypriv = &adapter->securitypriv;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u32 desired_encmode;
	u32 privacy;


	uint wps_ielen;

	int bselected = true;

	desired_encmode = psecuritypriv->ndisencryptstatus;
	privacy = pnetwork->network.Privacy;

	if (check_fwstate(pmlmepriv, WIFI_UNDER_WPS)) {
		if (rtw_get_wps_ie(pnetwork->network.IEs+_FIXED_IE_LENGTH_, pnetwork->network.IELength-_FIXED_IE_LENGTH_, NULL, &wps_ielen) != NULL)
			return true;
		else
			return false;
	}
	if (adapter->registrypriv.wifi_spec == 1) {
		if ((desired_encmode == Ndis802_11EncryptionDisabled) && (privacy != 0))
			bselected = false;
	}


	if ((desired_encmode != Ndis802_11EncryptionDisabled) && (privacy == 0)) {
		DBG_88E("desired_encmode: %d, privacy: %d\n", desired_encmode, privacy);
		bselected = false;
	}

	if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) {
		if (pnetwork->network.InfrastructureMode != pmlmepriv->cur_network.network.InfrastructureMode)
			bselected = false;
	}


	return bselected;
}
