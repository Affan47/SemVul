be_pci_sriov_configure(struct pci_dev *pdev, int num_vfs)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);
	u16 num_vf_qs;
	int status;

	if (!num_vfs)
		be_vf_clear(adapter);

	adapter->num_vfs = num_vfs;

	if (adapter->num_vfs == 0 && pci_vfs_assigned(pdev)) {
		dev_warn(&pdev->dev,
			 "Cannot disable VFs while they are assigned\n");
		return -EBUSY;
	}


	if (skyhawk_chip(adapter) && !pci_num_vf(pdev)) {
		num_vf_qs = be_calculate_vf_qs(adapter, adapter->num_vfs);
		status = be_cmd_set_sriov_config(adapter, adapter->pool_res,
						 adapter->num_vfs, num_vf_qs);
		if (status)
			dev_err(&pdev->dev,
				"Failed to optimize SR-IOV resources\n");
	}

	status = be_get_resources(adapter);
	if (status)
		return be_cmd_status(status);


	rtnl_lock();
	status = be_update_queues(adapter);
	rtnl_unlock();
	if (status)
		return be_cmd_status(status);

	if (adapter->num_vfs)
		status = be_vf_setup(adapter);

	if (!status)
		return adapter->num_vfs;

	return 0;
}
