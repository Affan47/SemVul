pcf50633_mbc_usb_curlim_set(struct pcf50633 *pcf, int ma)
{
	struct pcf50633_mbc *mbc = platform_get_drvdata(pcf->mbc_pdev);
	int ret = 0;
	u8 bits;
	int charging_start = 1;
	u8 mbcs2, chgmod;
	unsigned int mbcc5;

	if (ma >= 1000) {
		bits = PCF50633_MBCC7_USB_1000mA;
		ma = 1000;
	} else if (ma >= 500) {
		bits = PCF50633_MBCC7_USB_500mA;
		ma = 500;
	} else if (ma >= 100) {
		bits = PCF50633_MBCC7_USB_100mA;
		ma = 100;
	} else {
		bits = PCF50633_MBCC7_USB_SUSPEND;
		charging_start = 0;
		ma = 0;
	}

	ret = pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC7,
					PCF50633_MBCC7_USB_MASK, bits);
	if (ret)
		dev_err(pcf->dev, "error setting usb curlim to %d mA\n", ma);
	else
		dev_info(pcf->dev, "usb curlim to %d mA\n", ma);


	if (mbc->pcf->pdata->charger_reference_current_ma) {
		mbcc5 = (ma << 8) / mbc->pcf->pdata->charger_reference_current_ma;
		if (mbcc5 > 255)
			mbcc5 = 255;
		pcf50633_reg_write(mbc->pcf, PCF50633_REG_MBCC5, mbcc5);
	}

	mbcs2 = pcf50633_reg_read(mbc->pcf, PCF50633_REG_MBCS2);
	chgmod = (mbcs2 & PCF50633_MBCS2_MBC_MASK);


	if (chgmod != PCF50633_MBCS2_MBC_BAT_FULL)
		pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA, PCF50633_MBCC1_CHGENA);
	else {
		pcf50633_reg_clear_bits(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA);
		pcf50633_reg_set_bit_mask(pcf, PCF50633_REG_MBCC1,
				PCF50633_MBCC1_CHGENA, PCF50633_MBCC1_CHGENA);
	}

	power_supply_changed(mbc->usb);

	return ret;
}
