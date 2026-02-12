static u8 i40e_pf_get_tc_map(struct i40e_pf *pf)
{
	if (pf->flags & I40E_FLAG_TC_MQPRIO)
		return i40e_mqprio_get_enabled_tc(pf);


	if (!(pf->flags & I40E_FLAG_DCB_ENABLED))
		return I40E_DEFAULT_TRAFFIC_CLASS;


	if (!(pf->flags & I40E_FLAG_MFP_ENABLED))
		return i40e_dcb_get_enabled_tc(&pf->hw.local_dcbx_config);


	if (pf->hw.func_caps.iscsi)
		return i40e_get_iscsi_tc_map(pf);
	else
		return I40E_DEFAULT_TRAFFIC_CLASS;
}
