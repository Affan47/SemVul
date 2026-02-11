wl12xx_pre_upload(struct wl1271 *wl)
{
	u32 tmp;
	u16 polarity;
	int ret;


	wl1271_debug(DEBUG_BOOT, "ACX_EEPROMLESS_IND_REG");

	ret = wlcore_write32(wl, WL12XX_EEPROMLESS_IND, WL12XX_EEPROMLESS_IND);
	if (ret < 0)
		goto out;

	ret = wlcore_read_reg(wl, REG_CHIP_ID_B, &tmp);
	if (ret < 0)
		goto out;

	wl1271_debug(DEBUG_BOOT, "chip id 0x%x", tmp);


	ret = wlcore_read32(wl, WL12XX_SCR_PAD2, &tmp);
	if (ret < 0)
		goto out;


	if (wl->chip.id == CHIP_ID_128X_PG20) {
		ret = wl12xx_top_reg_write(wl, SDIO_IO_DS, HCI_IO_DS_6MA);
		if (ret < 0)
			goto out;
	}


	ret = wl12xx_top_reg_read(wl, OCP_REG_POLARITY, &polarity);
	if (ret < 0)
		goto out;


	polarity &= ~POLARITY_LOW;
	ret = wl12xx_top_reg_write(wl, OCP_REG_POLARITY, polarity);

out:
	return ret;
}
