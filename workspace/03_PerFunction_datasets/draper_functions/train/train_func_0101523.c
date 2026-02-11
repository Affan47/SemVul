ssd_check_hw(struct ssd_device *dev)
{
	uint32_t test_data = 0x55AA5AA5;
	uint32_t read_data;

	ssd_reg32_write(dev->ctrlp + SSD_BRIDGE_TEST_REG, test_data);
	read_data = ssd_reg32_read(dev->ctrlp + SSD_BRIDGE_TEST_REG);
	if (read_data != ~(test_data)) {

		return -1;
	}

	return 0;
}
