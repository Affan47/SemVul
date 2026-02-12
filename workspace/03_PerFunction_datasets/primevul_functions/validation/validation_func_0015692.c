static bool adv_use_rpa(struct hci_dev *hdev, uint32_t flags)
{

	if (!hci_dev_test_flag(hdev, HCI_PRIVACY))
		return false;


	if (!hci_dev_test_flag(hdev, HCI_LIMITED_PRIVACY))
		return true;


	if ((flags & MGMT_ADV_FLAG_DISCOV) &&
	    hci_dev_test_flag(hdev, HCI_BONDABLE))
		return false;


	return true;
}
