ds2482_w1_read_byte(void *data)
{
	struct ds2482_w1_chan *pchan = data;
	struct ds2482_data    *pdev = pchan->pdev;
	int result;

	mutex_lock(&pdev->access_lock);


	ds2482_wait_1wire_idle(pdev);
	if (pdev->w1_count > 1)
		ds2482_set_channel(pdev, pchan->channel);


	ds2482_send_cmd(pdev, DS2482_CMD_1WIRE_READ_BYTE);


	ds2482_wait_1wire_idle(pdev);


	ds2482_select_register(pdev, DS2482_PTR_CODE_DATA);


	result = i2c_smbus_read_byte(pdev->client);

	mutex_unlock(&pdev->access_lock);

	return result;
}
