__sst_write(u8 __iomem *vbase, u32 reg, u32 val)
{
	sst_dbg_print_write_reg(reg, val);
	writel(val, vbase + reg);
}
