static void xemaclite_disable_interrupts(struct net_local *drvdata)
{
	u32 reg_data;


	xemaclite_writel(XEL_GIER_GIE_MASK, drvdata->base_addr + XEL_GIER_OFFSET);


	reg_data = xemaclite_readl(drvdata->base_addr + XEL_TSR_OFFSET);
	xemaclite_writel(reg_data & (~XEL_TSR_XMIT_IE_MASK),
			 drvdata->base_addr + XEL_TSR_OFFSET);


	reg_data = xemaclite_readl(drvdata->base_addr + XEL_RSR_OFFSET);
	xemaclite_writel(reg_data & (~XEL_RSR_RECV_IE_MASK),
			 drvdata->base_addr + XEL_RSR_OFFSET);
}
