static void hci_cc_inquiry_cancel(struct hci_dev *hdev, struct sk_buff *skb,
				  u8 *new_status)
{
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);


	if (status == 0x0c && !test_bit(HCI_INQUIRY, &hdev->flags)) {
		bt_dev_warn(hdev, "Ignoring error of Inquiry Cancel command");
		status = 0x00;
	}

	*new_status = status;

	if (status)
		return;

	clear_bit(HCI_INQUIRY, &hdev->flags);
	smp_mb__after_atomic();
	wake_up_bit(&hdev->flags, HCI_INQUIRY);

	hci_dev_lock(hdev);


	if (!hci_dev_test_flag(hdev, HCI_LE_SCAN) ||
	    hdev->le_scan_type != LE_SCAN_ACTIVE)
		hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
	hci_dev_unlock(hdev);

	hci_conn_check_pending(hdev);
}
