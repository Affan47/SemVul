void hci_req_prepare_suspend(struct hci_dev *hdev, enum suspended_state next)
{
	int old_state;
	struct hci_conn *conn;
	struct hci_request req;
	u8 page_scan;
	int disconnect_counter;

	if (next == hdev->suspend_state) {
		bt_dev_dbg(hdev, "Same state before and after: %d", next);
		goto done;
	}

	hdev->suspend_state = next;
	hci_req_init(&req, hdev);

	if (next == BT_SUSPEND_DISCONNECT) {

		hdev->suspended = true;


		old_state = hdev->discovery.state;
		if (old_state != DISCOVERY_STOPPED) {
			set_bit(SUSPEND_PAUSE_DISCOVERY, hdev->suspend_tasks);
			hci_discovery_set_state(hdev, DISCOVERY_STOPPING);
			queue_work(hdev->req_workqueue, &hdev->discov_update);
		}

		hdev->discovery_paused = true;
		hdev->discovery_old_state = old_state;


		old_state = hci_dev_test_flag(hdev, HCI_ADVERTISING);
		if (old_state) {
			set_bit(SUSPEND_PAUSE_ADVERTISING, hdev->suspend_tasks);
			cancel_delayed_work(&hdev->discov_off);
			queue_delayed_work(hdev->req_workqueue,
					   &hdev->discov_off, 0);
		}


		if (hdev->adv_instance_cnt)
			__hci_req_pause_adv_instances(&req);

		hdev->advertising_paused = true;
		hdev->advertising_old_state = old_state;

		page_scan = SCAN_DISABLED;
		hci_req_add(&req, HCI_OP_WRITE_SCAN_ENABLE, 1, &page_scan);


		if (hci_dev_test_flag(hdev, HCI_LE_SCAN)) {
			cancel_interleave_scan(hdev);
			hci_req_add_le_scan_disable(&req, false);
		}


		hci_req_add_set_adv_filter_enable(&req, false);


		set_bit(SUSPEND_SCAN_DISABLE, hdev->suspend_tasks);


		hdev->scanning_paused = true;


		hci_req_run(&req, suspend_req_complete);

		disconnect_counter = 0;

		list_for_each_entry(conn, &hdev->conn_hash.list, list) {
			hci_disconnect(conn, HCI_ERROR_REMOTE_POWER_OFF);
			disconnect_counter++;
		}

		if (disconnect_counter > 0) {
			bt_dev_dbg(hdev,
				   "Had %d disconnects. Will wait on them",
				   disconnect_counter);
			set_bit(SUSPEND_DISCONNECTING, hdev->suspend_tasks);
		}
	} else if (next == BT_SUSPEND_CONFIGURE_WAKE) {

		hdev->scanning_paused = false;

		hci_req_set_event_filter(&req);

		__hci_update_background_scan(&req);

		hdev->scanning_paused = true;
		hci_req_run(&req, suspend_req_complete);
	} else {
		hdev->suspended = false;
		hdev->scanning_paused = false;

		hci_req_clear_event_filter(&req);

		__hci_update_background_scan(&req);

		hci_req_add_set_adv_filter_enable(&req, true);


		hdev->advertising_paused = false;
		if (hdev->advertising_old_state) {
			set_bit(SUSPEND_UNPAUSE_ADVERTISING,
				hdev->suspend_tasks);
			hci_dev_set_flag(hdev, HCI_ADVERTISING);
			queue_work(hdev->req_workqueue,
				   &hdev->discoverable_update);
			hdev->advertising_old_state = 0;
		}


		if (hdev->adv_instance_cnt)
			__hci_req_resume_adv_instances(&req);


		hdev->discovery_paused = false;
		if (hdev->discovery_old_state != DISCOVERY_STOPPED &&
		    hdev->discovery_old_state != DISCOVERY_STOPPING) {
			set_bit(SUSPEND_UNPAUSE_DISCOVERY, hdev->suspend_tasks);
			hci_discovery_set_state(hdev, DISCOVERY_STARTING);
			queue_work(hdev->req_workqueue, &hdev->discov_update);
		}

		hci_req_run(&req, suspend_req_complete);
	}

	hdev->suspend_state = next;

done:
	clear_bit(SUSPEND_PREPARE_NOTIFIER, hdev->suspend_tasks);
	wake_up(&hdev->suspend_wait_q);
}
