void hci_req_add_le_passive_scan(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	u8 own_addr_type;
	u8 filter_policy;
	u16 window, interval;

	bool addr_resolv = true;

	if (hdev->scanning_paused) {
		bt_dev_dbg(hdev, "Scanning is paused for suspend");
		return;
	}


	if (hci_update_random_address(req, false, scan_use_rpa(hdev),
				      &own_addr_type))
		return;

	if (hdev->enable_advmon_interleave_scan &&
	    __hci_update_interleaved_scan(hdev))
		return;

	bt_dev_dbg(hdev, "interleave state %d", hdev->interleave_scan_state);


	filter_policy = update_white_list(req);


	if (hci_dev_test_flag(hdev, HCI_PRIVACY) &&
	    (hdev->le_features[0] & HCI_LE_EXT_SCAN_POLICY))
		filter_policy |= 0x02;

	if (hdev->suspended) {
		window = hdev->le_scan_window_suspend;
		interval = hdev->le_scan_int_suspend;

		set_bit(SUSPEND_SCAN_ENABLE, hdev->suspend_tasks);
	} else if (hci_is_le_conn_scanning(hdev)) {
		window = hdev->le_scan_window_connect;
		interval = hdev->le_scan_int_connect;
	} else if (hci_is_adv_monitoring(hdev)) {
		window = hdev->le_scan_window_adv_monitor;
		interval = hdev->le_scan_int_adv_monitor;
	} else {
		window = hdev->le_scan_window;
		interval = hdev->le_scan_interval;
	}

	bt_dev_dbg(hdev, "LE passive scan with whitelist = %d", filter_policy);
	hci_req_start_scan(req, LE_SCAN_PASSIVE, interval, window,
			   own_addr_type, filter_policy, addr_resolv);
}
