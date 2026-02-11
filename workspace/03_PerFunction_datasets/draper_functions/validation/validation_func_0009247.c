sxgbe_set_tx_mtl_mode(void __iomem *ioaddr, int queue_num,
				  int tx_mode)
{
	u32 reg_val;

	reg_val = readl(ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));

	if (tx_mode == SXGBE_MTL_SFMODE) {
		reg_val |= SXGBE_MTL_SFMODE;
	} else {

		if (tx_mode <= 64)
			reg_val |= MTL_CONTROL_TTC_64;
		else if (tx_mode <= 96)
			reg_val |= MTL_CONTROL_TTC_96;
		else if (tx_mode <= 128)
			reg_val |= MTL_CONTROL_TTC_128;
		else if (tx_mode <= 192)
			reg_val |= MTL_CONTROL_TTC_192;
		else if (tx_mode <= 256)
			reg_val |= MTL_CONTROL_TTC_256;
		else if (tx_mode <= 384)
			reg_val |= MTL_CONTROL_TTC_384;
		else
			reg_val |= MTL_CONTROL_TTC_512;
	}


	writel(reg_val, ioaddr + SXGBE_MTL_TXQ_OPMODE_REG(queue_num));
}
