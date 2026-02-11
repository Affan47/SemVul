t3_io_error_detected(struct pci_dev *pdev,
					     pci_channel_state_t state)
{
	struct adapter *adapter = pci_get_drvdata(pdev);

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	t3_adapter_error(adapter, 0, 0);


	return PCI_ERS_RESULT_NEED_RESET;
}
