qla2x00_write_flash_byte(struct qla_hw_data *ha, uint32_t addr, uint8_t data)
{
	uint16_t bank_select;
	struct device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	bank_select = RD_REG_WORD(&reg->ctrl_status);
	if (IS_QLA2322(ha) || IS_QLA6322(ha)) {


		bank_select &= ~0xf8;
		bank_select |= addr >> 12 & 0xf0;
		bank_select |= CSR_FLASH_64K_BANK;
		WRT_REG_WORD(&reg->ctrl_status, bank_select);
		RD_REG_WORD(&reg->ctrl_status);

		WRT_REG_WORD(&reg->flash_address, (uint16_t)addr);
		RD_REG_WORD(&reg->ctrl_status);
		WRT_REG_WORD(&reg->flash_data, (uint16_t)data);
		RD_REG_WORD(&reg->ctrl_status);

		return;
	}


	if ((addr & BIT_16) && ((bank_select & CSR_FLASH_64K_BANK) == 0)) {
		bank_select |= CSR_FLASH_64K_BANK;
		WRT_REG_WORD(&reg->ctrl_status, bank_select);
		RD_REG_WORD(&reg->ctrl_status);
	} else if (((addr & BIT_16) == 0) &&
	    (bank_select & CSR_FLASH_64K_BANK)) {
		bank_select &= ~(CSR_FLASH_64K_BANK);
		WRT_REG_WORD(&reg->ctrl_status, bank_select);
		RD_REG_WORD(&reg->ctrl_status);
	}


	if (ha->pio_address) {
		WRT_REG_WORD_PIO(PIO_REG(ha, flash_address), (uint16_t)addr);
		WRT_REG_WORD_PIO(PIO_REG(ha, flash_data), (uint16_t)data);
	} else {
		WRT_REG_WORD(&reg->flash_address, (uint16_t)addr);
		RD_REG_WORD(&reg->ctrl_status);
		WRT_REG_WORD(&reg->flash_data, (uint16_t)data);
		RD_REG_WORD(&reg->ctrl_status);
	}
}
