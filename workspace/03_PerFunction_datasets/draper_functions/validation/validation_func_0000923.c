qla2x00_lock_nvram_access(struct qla_hw_data *ha)
{
	uint16_t data;
	struct device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	if (!IS_QLA2100(ha) && !IS_QLA2200(ha) && !IS_QLA2300(ha)) {
		data = RD_REG_WORD(&reg->nvram);
		while (data & NVR_BUSY) {
			udelay(100);
			data = RD_REG_WORD(&reg->nvram);
		}


		WRT_REG_WORD(&reg->u.isp2300.host_semaphore, 0x1);
		RD_REG_WORD(&reg->u.isp2300.host_semaphore);
		udelay(5);
		data = RD_REG_WORD(&reg->u.isp2300.host_semaphore);
		while ((data & BIT_0) == 0) {

			udelay(100);
			WRT_REG_WORD(&reg->u.isp2300.host_semaphore, 0x1);
			RD_REG_WORD(&reg->u.isp2300.host_semaphore);
			udelay(5);
			data = RD_REG_WORD(&reg->u.isp2300.host_semaphore);
		}
	}
}
