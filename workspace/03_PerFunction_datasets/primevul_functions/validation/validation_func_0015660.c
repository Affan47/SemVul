int __hci_req_hci_power_on(struct hci_dev *hdev)
{


	smp_register(hdev);

	return __hci_req_sync(hdev, powered_update_hci, 0, HCI_CMD_TIMEOUT,
			      NULL);
}
