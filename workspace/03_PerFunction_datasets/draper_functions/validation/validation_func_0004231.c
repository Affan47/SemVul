r8169_csi_read(struct rtl8169_private *tp, int addr)
{
	void __iomem *ioaddr = tp->mmio_addr;

	RTL_W32(CSIAR, (addr & CSIAR_ADDR_MASK) |
		CSIAR_BYTE_ENABLE << CSIAR_BYTE_ENABLE_SHIFT);

	return rtl_udelay_loop_wait_high(tp, &rtl_csiar_cond, 10, 100) ?
		RTL_R32(CSIDR) : ~0;
}
