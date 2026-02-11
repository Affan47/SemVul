st_nci_hci_dm_fwupd_start(struct nfc_dev *dev, void *data,
				     size_t data_len)
{
	int r;
	struct nci_dev *ndev = nfc_get_drvdata(dev);

	dev->fw_download_in_progress = true;
	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_HCI_DM_FWUPD_START, data, data_len, NULL);
	if (r)
		dev->fw_download_in_progress = false;

	return r;
}
