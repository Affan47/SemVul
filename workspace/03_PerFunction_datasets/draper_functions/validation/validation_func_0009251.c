be_load_fw(struct be_adapter *adapter, u8 *fw_file)
{
	const struct firmware *fw;
	int status;

	if (!netif_running(adapter->netdev)) {
		dev_err(&adapter->pdev->dev,
			"Firmware load not allowed (interface is down)\n");
		return -ENETDOWN;
	}

	status = request_firmware(&fw, fw_file, &adapter->pdev->dev);
	if (status)
		goto fw_exit;

	dev_info(&adapter->pdev->dev, "Flashing firmware file %s\n", fw_file);

	if (lancer_chip(adapter))
		status = lancer_fw_download(adapter, fw);
	else
		status = be_fw_download(adapter, fw);

	if (!status)
		be_cmd_get_fw_ver(adapter);

fw_exit:
	release_firmware(fw);
	return status;
}
