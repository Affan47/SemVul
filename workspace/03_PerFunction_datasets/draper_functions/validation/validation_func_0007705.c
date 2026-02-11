odm_RSSIMonitorCheckCE(struct odm_dm_struct *pDM_Odm)
{
	struct adapter *Adapter = pDM_Odm->Adapter;
	struct hal_data_8188e	*pHalData = GET_HAL_DATA(Adapter);
	struct dm_priv	*pdmpriv = &pHalData->dmpriv;
	int	i;
	int	tmpEntryMaxPWDB = 0, tmpEntryMinPWDB = 0xff;
	u8	sta_cnt = 0;
	u32 PWDB_rssi[NUM_STA] = {0};
	struct sta_info *psta;
	u8 bcast_addr[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	if (!check_fwstate(&Adapter->mlmepriv, _FW_LINKED))
		return;

	for (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) {
		psta = pDM_Odm->pODM_StaInfo[i];
		if (IS_STA_VALID(psta) &&
		    (psta->state & WIFI_ASOC_STATE) &&
		    memcmp(psta->hwaddr, bcast_addr, ETH_ALEN) &&
		    memcmp(psta->hwaddr, myid(&Adapter->eeprompriv), ETH_ALEN)) {
			if (psta->rssi_stat.UndecoratedSmoothedPWDB < tmpEntryMinPWDB)
				tmpEntryMinPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

			if (psta->rssi_stat.UndecoratedSmoothedPWDB > tmpEntryMaxPWDB)
				tmpEntryMaxPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;
			if (psta->rssi_stat.UndecoratedSmoothedPWDB != (-1))
				PWDB_rssi[sta_cnt++] = (psta->mac_id | (psta->rssi_stat.UndecoratedSmoothedPWDB<<16));
		}
	}

	for (i = 0; i < sta_cnt; i++) {
		if (PWDB_rssi[i] != 0) {
			ODM_RA_SetRSSI_8188E(&pHalData->odmpriv,
					     PWDB_rssi[i] & 0xFF,
					     (PWDB_rssi[i] >> 16) & 0xFF);
		}
	}

	if (tmpEntryMaxPWDB != 0)
		pdmpriv->EntryMaxUndecoratedSmoothedPWDB = tmpEntryMaxPWDB;
	else
		pdmpriv->EntryMaxUndecoratedSmoothedPWDB = 0;

	if (tmpEntryMinPWDB != 0xff)
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = tmpEntryMinPWDB;
	else
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = 0;

	FindMinimumRSSI(Adapter);
	ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_RSSI_MIN,
			  pdmpriv->MinUndecoratedPWDBForDM);
}
