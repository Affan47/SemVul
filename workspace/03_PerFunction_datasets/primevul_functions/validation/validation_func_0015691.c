static u8 update_white_list(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	struct hci_conn_params *params;
	struct bdaddr_list *b;
	u8 num_entries = 0;
	bool pend_conn, pend_report;


	bool allow_rpa = hdev->suspended;


	list_for_each_entry(b, &hdev->le_white_list, list) {
		pend_conn = hci_pend_le_action_lookup(&hdev->pend_le_conns,
						      &b->bdaddr,
						      b->bdaddr_type);
		pend_report = hci_pend_le_action_lookup(&hdev->pend_le_reports,
							&b->bdaddr,
							b->bdaddr_type);


		if (!pend_conn && !pend_report) {
			del_from_white_list(req, &b->bdaddr, b->bdaddr_type);
			continue;
		}


		if (!allow_rpa &&
		    !hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY) &&
		    hci_find_irk_by_addr(hdev, &b->bdaddr, b->bdaddr_type)) {
			return 0x00;
		}

		num_entries++;
	}


	list_for_each_entry(params, &hdev->pend_le_conns, action) {
		if (add_to_white_list(req, params, &num_entries, allow_rpa))
			return 0x00;
	}


	list_for_each_entry(params, &hdev->pend_le_reports, action) {
		if (add_to_white_list(req, params, &num_entries, allow_rpa))
			return 0x00;
	}


	if (!idr_is_empty(&hdev->adv_monitors_idr) && !hdev->suspended &&
	    hci_get_adv_monitor_offload_ext(hdev) == HCI_ADV_MONITOR_EXT_NONE &&
	    hdev->interleave_scan_state != INTERLEAVE_SCAN_ALLOWLIST)
		return 0x00;


	return 0x01;
}
