odm_RATxRPTTimerSetting(
		struct odm_dm_struct *dm_odm,
		u16 minRptTime
)
{
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE, (" =====>odm_RATxRPTTimerSetting()\n"));

	if (dm_odm->CurrminRptTime != minRptTime) {
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			     (" CurrminRptTime = 0x%04x minRptTime = 0x%04x\n", dm_odm->CurrminRptTime, minRptTime));
		rtw_rpt_timer_cfg_cmd(dm_odm->Adapter, minRptTime);
		dm_odm->CurrminRptTime = minRptTime;
	}
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE, (" <===== odm_RATxRPTTimerSetting()\n"));
}
