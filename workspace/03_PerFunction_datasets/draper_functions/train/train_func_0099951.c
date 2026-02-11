ssd_check_pl_cap_fast(struct ssd_device *dev)
{
	uint32_t u1;
	uint16_t val = 0;
	int ret = 0;

	if (dev->protocol_info.ver < SSD_PROTOCOL_V3_2) {
		return 0;
	}

	if (dev->hw_info_ext.form_factor == SSD_FORM_FACTOR_FHHL && dev->hw_info.pcb_ver < 'B') {
		return 0;
	}


	ret = ssd_smbus_read_word(dev, SSD_SENSOR_LM80_SADDRESS, SSD_PL_CAP_U1, (uint8_t *)&val);
	if (ret) {
		goto out;
	}
	u1 = SSD_LM80_CONVERT_VOLT(u16_swap(val));
	if (SSD_PL_CAP_VOLT(u1) < SSD_PL_CAP_VOLT_READY) {
		ret = 1;
	}

out:
	return ret;
}
