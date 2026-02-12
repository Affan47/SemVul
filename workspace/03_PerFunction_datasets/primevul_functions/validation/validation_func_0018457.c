static struct hci_conn *check_pending_le_conn(struct hci_dev *hdev,
					      bdaddr_t *addr,
					      u8 addr_type, u8 adv_type,
					      bdaddr_t *direct_rpa)
{
	struct hci_conn *conn;
	struct hci_conn_params *params;


	if (adv_type != LE_ADV_IND && adv_type != LE_ADV_DIRECT_IND)
		return NULL;


	if (hci_bdaddr_list_lookup(&hdev->blacklist, addr, addr_type))
		return NULL;


	if (hdev->conn_hash.le_num_slave > 0 &&
	    (!test_bit(HCI_QUIRK_VALID_LE_STATES, &hdev->quirks) ||
	     !(hdev->le_states[3] & 0x10)))
		return NULL;


	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, addr,
					   addr_type);
	if (!params)
		return NULL;

	if (!params->explicit_connect) {
		switch (params->auto_connect) {
		case HCI_AUTO_CONN_DIRECT:


			if (adv_type != LE_ADV_DIRECT_IND)
				return NULL;
			break;
		case HCI_AUTO_CONN_ALWAYS:


			break;
		default:
			return NULL;
		}
	}

	conn = hci_connect_le(hdev, addr, addr_type, BT_SECURITY_LOW,
			      hdev->def_le_autoconnect_timeout, HCI_ROLE_MASTER,
			      direct_rpa);
	if (!IS_ERR(conn)) {


		if (!params->explicit_connect)
			params->conn = hci_conn_get(conn);

		return conn;
	}

	switch (PTR_ERR(conn)) {
	case -EBUSY:


		break;
	default:
		BT_DBG("Failed to connect: err %ld", PTR_ERR(conn));
		return NULL;
	}

	return NULL;
}
