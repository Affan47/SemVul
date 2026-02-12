static int __maybe_unused i40e_suspend(struct device *dev)
{
	struct i40e_pf *pf = dev_get_drvdata(dev);
	struct i40e_hw *hw = &pf->hw;


	if (test_and_set_bit(__I40E_SUSPENDED, pf->state))
		return 0;

	set_bit(__I40E_DOWN, pf->state);


	del_timer_sync(&pf->service_timer);
	cancel_work_sync(&pf->service_task);


	i40e_notify_client_of_netdev_close(pf->vsi[pf->lan_vsi], false);

	if (pf->wol_en && (pf->hw_features & I40E_HW_WOL_MC_MAGIC_PKT_WAKE))
		i40e_enable_mc_magic_wake(pf);


	rtnl_lock();

	i40e_prep_for_reset(pf, true);

	wr32(hw, I40E_PFPM_APM, (pf->wol_en ? I40E_PFPM_APM_APME_MASK : 0));
	wr32(hw, I40E_PFPM_WUFC, (pf->wol_en ? I40E_PFPM_WUFC_MAG_MASK : 0));


	i40e_clear_interrupt_scheme(pf);

	rtnl_unlock();

	return 0;
}
