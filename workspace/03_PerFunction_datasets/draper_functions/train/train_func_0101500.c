rtl88eu_phy_lc_calibrate(struct adapter *adapt)
{
	bool singletone = false, carrier_sup = false;
	u32 timeout = 2000, timecount = 0;
	struct hal_data_8188e *hal_data = GET_HAL_DATA(adapt);
	struct odm_dm_struct *dm_odm = &hal_data->odmpriv;

	if (!(dm_odm->SupportAbility & ODM_RF_CALIBRATION))
		return;
	if (singletone || carrier_sup)
		return;

	while (*(dm_odm->pbScanInProcess) && timecount < timeout) {
		mdelay(50);
		timecount += 50;
	}

	dm_odm->RFCalibrateInfo.bLCKInProgress = true;

	if (dm_odm->RFType == ODM_2T2R) {
		phy_lc_calibrate(adapt, true);
	} else {

		phy_lc_calibrate(adapt, false);
	}

	dm_odm->RFCalibrateInfo.bLCKInProgress = false;
}
