rtl8723a_init_default_value(struct rtw_adapter *padapter)
{
	struct hal_data_8723a *pHalData;
	struct dm_priv *pdmpriv;
	u8 i;

	pHalData = GET_HAL_DATA(padapter);
	pdmpriv = &pHalData->dmpriv;


	pHalData->bIQKInitialized = false;
	if (!padapter->pwrctrlpriv.bkeepfwalive)
		pHalData->LastHMEBoxNum = 0;

	pHalData->bIQKInitialized = false;


	pdmpriv->TM_Trigger = 0;


	pdmpriv->ThermalValue_HP_index = 0;
	for (i = 0; i < HP_THERMAL_NUM; i++)
		pdmpriv->ThermalValue_HP[i] = 0;


	pHalData->EfuseUsedBytes = 0;
	pHalData->BTEfuseUsedBytes = 0;
}
