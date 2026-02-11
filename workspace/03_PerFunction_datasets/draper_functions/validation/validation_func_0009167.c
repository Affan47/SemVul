update_bcn_erpinfo_ie(struct rtw_adapter *padapter)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	unsigned char *p, *ie = pnetwork->IEs;
	u32 len = 0;

	DBG_8723A("%s, ERP_enable =%d\n", __func__, pmlmeinfo->ERP_enable);

	if (!pmlmeinfo->ERP_enable)
		return;


	p = rtw_get_ie23a(ie, WLAN_EID_ERP_INFO, &len, pnetwork->IELength);
	if (p && len > 0) {
		if (pmlmepriv->num_sta_non_erp == 1)
			p[2] |= WLAN_ERP_NON_ERP_PRESENT |
				WLAN_ERP_USE_PROTECTION;
		else
			p[2] &= ~(WLAN_ERP_NON_ERP_PRESENT |
				  WLAN_ERP_USE_PROTECTION);

		if (pmlmepriv->num_sta_no_short_preamble > 0)
			p[2] |= WLAN_ERP_BARKER_PREAMBLE;
		else
			p[2] &= ~(WLAN_ERP_BARKER_PREAMBLE);

		ERP_IE_handler23a(padapter, p);
	}
}
