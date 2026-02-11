spi_block_write(struct stmpe *stmpe, u8 reg, u8 length,
		const u8 *values)
{
	int ret = 0, i;

	for (i = length; i > 0; i--, reg++) {
		ret = spi_reg_write(stmpe, reg, *(values + i - 1));
		if (ret < 0)
			return ret;
	}

	return ret;
}
