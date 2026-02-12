static int xemaclite_send_data(struct net_local *drvdata, u8 *data,
			       unsigned int byte_count)
{
	u32 reg_data;
	void __iomem *addr;


	addr = drvdata->base_addr + drvdata->next_tx_buf_to_use;


	if (byte_count > ETH_FRAME_LEN)
		byte_count = ETH_FRAME_LEN;


	reg_data = xemaclite_readl(addr + XEL_TSR_OFFSET);
	if ((reg_data & (XEL_TSR_XMIT_BUSY_MASK |
	     XEL_TSR_XMIT_ACTIVE_MASK)) == 0) {


		if (drvdata->tx_ping_pong != 0)
			drvdata->next_tx_buf_to_use ^= XEL_BUFFER_OFFSET;
	} else if (drvdata->tx_ping_pong != 0) {


		addr = (void __iomem __force *)((uintptr_t __force)addr ^
						 XEL_BUFFER_OFFSET);
		reg_data = xemaclite_readl(addr + XEL_TSR_OFFSET);

		if ((reg_data & (XEL_TSR_XMIT_BUSY_MASK |
		     XEL_TSR_XMIT_ACTIVE_MASK)) != 0)
			return -1;
	} else
		return -1;


	xemaclite_aligned_write(data, (u32 __force *)addr, byte_count);

	xemaclite_writel((byte_count & XEL_TPLR_LENGTH_MASK),
			 addr + XEL_TPLR_OFFSET);


	reg_data = xemaclite_readl(addr + XEL_TSR_OFFSET);
	reg_data |= (XEL_TSR_XMIT_BUSY_MASK | XEL_TSR_XMIT_ACTIVE_MASK);
	xemaclite_writel(reg_data, addr + XEL_TSR_OFFSET);

	return 0;
}
