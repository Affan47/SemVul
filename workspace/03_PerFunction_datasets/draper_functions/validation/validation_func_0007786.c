qlcnic_sriov_pf_disable(struct qlcnic_adapter *adapter)
{
	if (!qlcnic_sriov_pf_check(adapter))
		return;

	if (!qlcnic_sriov_enable_check(adapter))
		return;

	pci_disable_sriov(adapter->pdev);
	netdev_info(adapter->netdev,
		    "SR-IOV is disabled successfully on port %d\n",
		    adapter->portnum);
}
