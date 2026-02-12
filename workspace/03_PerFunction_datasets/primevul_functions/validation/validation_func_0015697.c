static int connectable_update(struct hci_request *req, unsigned long opt)
{
	struct hci_dev *hdev = req->hdev;

	hci_dev_lock(hdev);

	__hci_req_update_scan(req);


	if (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		__hci_req_update_adv_data(req, hdev->cur_adv_instance);


	if (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
	    !list_empty(&hdev->adv_instances)) {
		if (ext_adv_capable(hdev))
			__hci_req_start_ext_adv(req, hdev->cur_adv_instance);
		else
			__hci_req_enable_advertising(req);
	}

	__hci_update_background_scan(req);

	hci_dev_unlock(hdev);

	return 0;
}
