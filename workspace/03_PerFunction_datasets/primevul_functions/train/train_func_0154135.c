static int i40e_init_recovery_mode(struct i40e_pf *pf, struct i40e_hw *hw)
{
	struct i40e_vsi *vsi;
	int err;
	int v_idx;

	pci_save_state(pf->pdev);


	timer_setup(&pf->service_timer, i40e_service_timer, 0);
	pf->service_timer_period = HZ;

	INIT_WORK(&pf->service_task, i40e_service_task);
	clear_bit(__I40E_SERVICE_SCHED, pf->state);

	err = i40e_init_interrupt_scheme(pf);
	if (err)
		goto err_switch_setup;


	if (pf->hw.func_caps.num_vsis < I40E_MIN_VSI_ALLOC)
		pf->num_alloc_vsi = I40E_MIN_VSI_ALLOC;
	else
		pf->num_alloc_vsi = pf->hw.func_caps.num_vsis;


	pf->vsi = kcalloc(pf->num_alloc_vsi, sizeof(struct i40e_vsi *),
			  GFP_KERNEL);
	if (!pf->vsi) {
		err = -ENOMEM;
		goto err_switch_setup;
	}


	v_idx = i40e_vsi_mem_alloc(pf, I40E_VSI_MAIN);
	if (v_idx < 0)
		goto err_switch_setup;
	pf->lan_vsi = v_idx;
	vsi = pf->vsi[v_idx];
	if (!vsi)
		goto err_switch_setup;
	vsi->alloc_queue_pairs = 1;
	err = i40e_config_netdev(vsi);
	if (err)
		goto err_switch_setup;
	err = register_netdev(vsi->netdev);
	if (err)
		goto err_switch_setup;
	vsi->netdev_registered = true;
	i40e_dbg_pf_init(pf);

	err = i40e_setup_misc_vector_for_recovery_mode(pf);
	if (err)
		goto err_switch_setup;


	i40e_send_version(pf);


	mod_timer(&pf->service_timer,
		  round_jiffies(jiffies + pf->service_timer_period));

	return 0;

err_switch_setup:
	i40e_reset_interrupt_capability(pf);
	del_timer_sync(&pf->service_timer);
	i40e_shutdown_adminq(hw);
	iounmap(hw->hw_addr);
	pci_disable_pcie_error_reporting(pf->pdev);
	pci_release_mem_regions(pf->pdev);
	pci_disable_device(pf->pdev);
	kfree(pf);

	return err;
}
