static bool is_advertising_allowed(struct hci_dev *hdev, bool connectable)
{

	if (hci_conn_num(hdev, LE_LINK) == 0)
		return true;


	if (hdev->conn_hash.le_num_slave > 0) {

		if (!connectable && !(hdev->le_states[2] & 0x10))
			return false;


		if (connectable && (!(hdev->le_states[4] & 0x40) ||
				    !(hdev->le_states[2] & 0x20)))
			return false;
	}


	if (hci_conn_num(hdev, LE_LINK) != hdev->conn_hash.le_num_slave) {

		if (!connectable && !(hdev->le_states[2] & 0x02))
			return false;


		if (connectable && (!(hdev->le_states[4] & 0x08) ||
				    !(hdev->le_states[2] & 0x08)))
			return false;
	}

	return true;
}
