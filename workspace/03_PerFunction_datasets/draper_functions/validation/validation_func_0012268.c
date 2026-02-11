pcie_aspm_pm_state_change(struct pci_dev *pdev)
{
	struct pcie_link_state *link = pdev->link_state;

	if (aspm_disabled || !link)
		return;


	down_read(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	pcie_update_aspm_capable(link->root);
	pcie_config_aspm_path(link);
	mutex_unlock(&aspm_lock);
	up_read(&pci_bus_sem);
}
