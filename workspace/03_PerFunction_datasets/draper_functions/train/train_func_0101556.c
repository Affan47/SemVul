r852_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct r852_device *dev = r852_get_dev(mtd);
	uint32_t reg;

	if (dev->card_unstable) {


		memset(buf, 0, len);
		return;
	}


	if (len == R852_DMA_LEN && dev->dma_usable) {
		r852_do_dma(dev, buf, 1);
		return;
	}


	while (len >= 4) {

		reg = r852_read_reg_dword(dev, R852_DATALINE);
		*buf++ = reg & 0xFF;
		*buf++ = (reg >> 8) & 0xFF;
		*buf++ = (reg >> 16) & 0xFF;
		*buf++ = (reg >> 24) & 0xFF;
		len -= 4;
	}


	while (len--)
		*buf++ = r852_read_reg(dev, R852_DATALINE);
}
