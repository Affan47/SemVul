bt_ti_probe(struct platform_device *pdev)
{
	static struct ti_st *hst;
	struct hci_dev *hdev;
	int err;

	hst = devm_kzalloc(&pdev->dev, sizeof(struct ti_st), GFP_KERNEL);
	if (!hst)
		return -ENOMEM;


	hdev = hci_alloc_dev();
	if (!hdev)
		return -ENOMEM;

	BT_DBG("hdev %p", hdev);

	hst->hdev = hdev;
	hdev->bus = HCI_UART;
	hci_set_drvdata(hdev, hst);
	hdev->open = ti_st_open;
	hdev->close = ti_st_close;
	hdev->flush = NULL;
	hdev->send = ti_st_send_frame;

	err = hci_register_dev(hdev);
	if (err < 0) {
		BT_ERR("Can't register HCI device error %d", err);
		hci_free_dev(hdev);
		return err;
	}

	BT_DBG("HCI device registered (hdev %p)", hdev);

	dev_set_drvdata(&pdev->dev, hst);
	return err;
}
