static u8 bredr_oob_data_present(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;
	struct oob_data *data;

	data = hci_find_remote_oob_data(hdev, &conn->dst, BDADDR_BREDR);
	if (!data)
		return 0x00;

	if (bredr_sc_enabled(hdev)) {


		if (!hci_dev_test_flag(hdev, HCI_SC_ONLY))
			return data->present;


		if (!memcmp(data->rand256, ZERO_KEY, 16) ||
		    !memcmp(data->hash256, ZERO_KEY, 16))
			return 0x00;

		return 0x02;
	}


	if (!memcmp(data->rand192, ZERO_KEY, 16) ||
	    !memcmp(data->hash192, ZERO_KEY, 16))
		return 0x00;

	return 0x01;
}
