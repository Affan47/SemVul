xiic_start_send(struct xiic_i2c *i2c)
{
	struct i2c_msg *msg = i2c->tx_msg;

	xiic_irq_clr(i2c, XIIC_INTR_TX_ERROR_MASK);

	dev_dbg(i2c->adap.dev.parent, "%s entry, msg: %p, len: %d",
		__func__, msg, msg->len);
	dev_dbg(i2c->adap.dev.parent, "%s entry, ISR: 0x%x, CR: 0x%x\n",
		__func__, xiic_getreg32(i2c, XIIC_IISR_OFFSET),
		xiic_getreg8(i2c, XIIC_CR_REG_OFFSET));

	if (!(msg->flags & I2C_M_NOSTART)) {

		u16 data = ((msg->addr << 1) & 0xfe) | XIIC_WRITE_OPERATION |
			XIIC_TX_DYN_START_MASK;
		if ((i2c->nmsgs == 1) && msg->len == 0)

			data |= XIIC_TX_DYN_STOP_MASK;

		xiic_setreg16(i2c, XIIC_DTR_REG_OFFSET, data);
	}

	xiic_fill_tx_fifo(i2c);


	xiic_irq_clr_en(i2c, XIIC_INTR_TX_EMPTY_MASK | XIIC_INTR_TX_ERROR_MASK |
		XIIC_INTR_BNB_MASK);
}
