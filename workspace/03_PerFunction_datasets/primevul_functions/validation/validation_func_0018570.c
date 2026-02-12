static void hci_cs_le_create_conn(struct hci_dev *hdev, u8 status)
{
	struct hci_cp_le_create_conn *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);


	if (status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_CREATE_CONN);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	cs_le_create_conn(hdev, &cp->peer_addr, cp->peer_addr_type,
			  cp->own_address_type, cp->filter_policy);

	hci_dev_unlock(hdev);
}
