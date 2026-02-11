enc28j60_set_bank(struct enc28j60_net *priv, u8 addr)
{
	u8 b = (addr & BANK_MASK) >> 5;


	if (addr >= EIE && addr <= ECON1)
		return;


	if ((b & ECON1_BSEL0) != (priv->bank & ECON1_BSEL0)) {
		if (b & ECON1_BSEL0)
			spi_write_op(priv, ENC28J60_BIT_FIELD_SET, ECON1,
					ECON1_BSEL0);
		else
			spi_write_op(priv, ENC28J60_BIT_FIELD_CLR, ECON1,
					ECON1_BSEL0);
	}
	if ((b & ECON1_BSEL1) != (priv->bank & ECON1_BSEL1)) {
		if (b & ECON1_BSEL1)
			spi_write_op(priv, ENC28J60_BIT_FIELD_SET, ECON1,
					ECON1_BSEL1);
		else
			spi_write_op(priv, ENC28J60_BIT_FIELD_CLR, ECON1,
					ECON1_BSEL1);
	}
	priv->bank = b;
}
