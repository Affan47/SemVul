btintel_set_diag_mfg(struct hci_dev *hdev, bool enable)
{
	struct sk_buff *skb;
	u8 param[2];
	int err;

	param[0] = 0x01;
	param[1] = 0x00;

	skb = __hci_cmd_sync(hdev, 0xfc11, 2, param, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		err = PTR_ERR(skb);
		BT_ERR("%s: Entering Intel manufacturer mode failed (%d)",
		       hdev->name, err);
		return PTR_ERR(skb);
	}
	kfree_skb(skb);

	err = btintel_set_diag(hdev, enable);

	param[0] = 0x00;
	param[1] = 0x00;

	skb = __hci_cmd_sync(hdev, 0xfc11, 2, param, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		err = PTR_ERR(skb);
		BT_ERR("%s: Leaving Intel manufacturer mode failed (%d)",
		       hdev->name, err);
		return PTR_ERR(skb);
	}
	kfree_skb(skb);

	return err;
}
