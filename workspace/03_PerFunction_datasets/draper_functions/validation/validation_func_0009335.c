regmap_encx24j600_read(void *context,
				  const void *reg_buf, size_t reg_size,
				  void *val, size_t val_size)
{
	u8 reg = *(const u8 *)reg_buf;

	if (reg_size != 1) {
		pr_err("%s: reg=%02x reg_size=%zu\n", __func__, reg, reg_size);
		return -EINVAL;
	}

	if (reg > 0xa0)
		return regmap_encx24j600_spi_read(context, reg, val, val_size);

	if (val_size > 2) {
		pr_err("%s: reg=%02x val_size=%zu\n", __func__, reg, val_size);
		return -EINVAL;
	}

	return regmap_encx24j600_sfr_read(context, reg, val, val_size);
}
