pn544_hci_discover_se(struct nfc_hci_dev *hdev)
{
	u32 se_idx = 0;
	u8 ese_mode = 0x01;
	struct sk_buff *res_skb;
	int r;

	r = nfc_hci_send_cmd(hdev, PN544_SYS_MGMT_GATE, PN544_TEST_SWP,
			     NULL, 0, &res_skb);

	if (r == 0) {
		if (res_skb->len == 2 && res_skb->data[0] == 0x00)
			nfc_add_se(hdev->ndev, se_idx++, NFC_SE_UICC);

		kfree_skb(res_skb);
	}

	r = nfc_hci_send_event(hdev, PN544_NFC_WI_MGMT_GATE,
				PN544_HCI_EVT_SWITCH_MODE,
				&ese_mode, 1);
	if (r == 0)
		nfc_add_se(hdev->ndev, se_idx++, NFC_SE_EMBEDDED);

	return !se_idx;
}
