static void le_conn_complete_evt(struct hci_dev *hdev, u8 status,
			bdaddr_t *bdaddr, u8 bdaddr_type, u8 role, u16 handle,
			u16 interval, u16 latency, u16 supervision_timeout)
{
	struct hci_conn_params *params;
	struct hci_conn *conn;
	struct smp_irk *irk;
	u8 addr_type;

	hci_dev_lock(hdev);


	hci_dev_clear_flag(hdev, HCI_LE_ADV);

	conn = hci_lookup_le_connect(hdev);
	if (!conn) {
		conn = hci_conn_add(hdev, LE_LINK, bdaddr, role);
		if (!conn) {
			bt_dev_err(hdev, "no memory for new connection");
			goto unlock;
		}

		conn->dst_type = bdaddr_type;


		if (conn->out) {
			conn->resp_addr_type = bdaddr_type;
			bacpy(&conn->resp_addr, bdaddr);
			if (hci_dev_test_flag(hdev, HCI_PRIVACY)) {
				conn->init_addr_type = ADDR_LE_DEV_RANDOM;
				bacpy(&conn->init_addr, &hdev->rpa);
			} else {
				hci_copy_identity_address(hdev,
							  &conn->init_addr,
							  &conn->init_addr_type);
			}
		}
	} else {
		cancel_delayed_work(&conn->le_conn_timeout);
	}

	if (!conn->out) {


		conn->resp_addr_type = hdev->adv_addr_type;
		if (hdev->adv_addr_type == ADDR_LE_DEV_RANDOM) {


			if (!ext_adv_capable(hdev))
				bacpy(&conn->resp_addr, &hdev->random_addr);
		} else {
			bacpy(&conn->resp_addr, &hdev->bdaddr);
		}

		conn->init_addr_type = bdaddr_type;
		bacpy(&conn->init_addr, bdaddr);


		conn->le_conn_min_interval = hdev->le_conn_min_interval;
		conn->le_conn_max_interval = hdev->le_conn_max_interval;
	}


	irk = hci_get_irk(hdev, &conn->dst, conn->dst_type);
	if (irk) {
		bacpy(&conn->dst, &irk->bdaddr);
		conn->dst_type = irk->addr_type;
	}

	if (status) {
		hci_le_conn_failed(conn, status);
		goto unlock;
	}

	if (conn->dst_type == ADDR_LE_DEV_PUBLIC)
		addr_type = BDADDR_LE_PUBLIC;
	else
		addr_type = BDADDR_LE_RANDOM;


	if (hci_bdaddr_list_lookup(&hdev->blacklist, &conn->dst, addr_type)) {
		hci_conn_drop(conn);
		goto unlock;
	}

	if (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, NULL, 0);

	conn->sec_level = BT_SECURITY_LOW;
	conn->handle = handle;
	conn->state = BT_CONFIG;

	conn->le_conn_interval = interval;
	conn->le_conn_latency = latency;
	conn->le_supv_timeout = supervision_timeout;

	hci_debugfs_create_conn(conn);
	hci_conn_add_sysfs(conn);


	if (conn->out ||
	    (hdev->le_features[0] & HCI_LE_SLAVE_FEATURES)) {
		struct hci_cp_le_read_remote_features cp;

		cp.handle = __cpu_to_le16(conn->handle);

		hci_send_cmd(hdev, HCI_OP_LE_READ_REMOTE_FEATURES,
			     sizeof(cp), &cp);

		hci_conn_hold(conn);
	} else {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, status);
	}

	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, &conn->dst,
					   conn->dst_type);
	if (params) {
		list_del_init(&params->action);
		if (params->conn) {
			hci_conn_drop(params->conn);
			hci_conn_put(params->conn);
			params->conn = NULL;
		}
	}

unlock:
	hci_update_background_scan(hdev);
	hci_dev_unlock(hdev);
}
