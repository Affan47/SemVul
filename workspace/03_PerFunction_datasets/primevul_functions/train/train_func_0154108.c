static void i40e_remove(struct pci_dev *pdev)
{
	struct i40e_pf *pf = pci_get_drvdata(pdev);
	struct i40e_hw *hw = &pf->hw;
	i40e_status ret_code;
	int i;

	i40e_dbg_pf_exit(pf);

	i40e_ptp_stop(pf);


	i40e_write_rx_ctl(hw, I40E_PFQF_HENA(0), 0);
	i40e_write_rx_ctl(hw, I40E_PFQF_HENA(1), 0);


	set_bit(__I40E_SUSPENDED, pf->state);
	set_bit(__I40E_DOWN, pf->state);
	if (pf->service_timer.function)
		del_timer_sync(&pf->service_timer);
	if (pf->service_task.func)
		cancel_work_sync(&pf->service_task);

	if (test_bit(__I40E_RECOVERY_MODE, pf->state)) {
		struct i40e_vsi *vsi = pf->vsi[0];


		unregister_netdev(vsi->netdev);
		free_netdev(vsi->netdev);

		goto unmap;
	}


	i40e_notify_client_of_netdev_close(pf->vsi[pf->lan_vsi], false);

	if (pf->flags & I40E_FLAG_SRIOV_ENABLED) {
		i40e_free_vfs(pf);
		pf->flags &= ~I40E_FLAG_SRIOV_ENABLED;
	}

	i40e_fdir_teardown(pf);


	for (i = 0; i < I40E_MAX_VEB; i++) {
		if (!pf->veb[i])
			continue;

		if (pf->veb[i]->uplink_seid == pf->mac_seid ||
		    pf->veb[i]->uplink_seid == 0)
			i40e_switch_branch_release(pf->veb[i]);
	}


	if (pf->vsi[pf->lan_vsi])
		i40e_vsi_release(pf->vsi[pf->lan_vsi]);

	i40e_cloud_filter_exit(pf);


	if (pf->flags & I40E_FLAG_IWARP_ENABLED) {
		ret_code = i40e_lan_del_device(pf);
		if (ret_code)
			dev_warn(&pdev->dev, "Failed to delete client device: %d\n",
				 ret_code);
	}


	if (hw->hmc.hmc_obj) {
		ret_code = i40e_shutdown_lan_hmc(hw);
		if (ret_code)
			dev_warn(&pdev->dev,
				 "Failed to destroy the HMC resources: %d\n",
				 ret_code);
	}

unmap:

	if (test_bit(__I40E_RECOVERY_MODE, pf->state) &&
	    !(pf->flags & I40E_FLAG_MSIX_ENABLED))
		free_irq(pf->pdev->irq, pf);


	i40e_shutdown_adminq(hw);


	mutex_destroy(&hw->aq.arq_mutex);
	mutex_destroy(&hw->aq.asq_mutex);


	rtnl_lock();
	i40e_clear_interrupt_scheme(pf);
	for (i = 0; i < pf->num_alloc_vsi; i++) {
		if (pf->vsi[i]) {
			if (!test_bit(__I40E_RECOVERY_MODE, pf->state))
				i40e_vsi_clear_rings(pf->vsi[i]);
			i40e_vsi_clear(pf->vsi[i]);
			pf->vsi[i] = NULL;
		}
	}
	rtnl_unlock();

	for (i = 0; i < I40E_MAX_VEB; i++) {
		kfree(pf->veb[i]);
		pf->veb[i] = NULL;
	}

	kfree(pf->qp_pile);
	kfree(pf->vsi);

	iounmap(hw->hw_addr);
	kfree(pf);
	pci_release_mem_regions(pdev);

	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
}
