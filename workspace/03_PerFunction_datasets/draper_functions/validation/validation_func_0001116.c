set_signals(struct slgt_info *info)
{
	unsigned char val = rd_reg8(info, VCR);
	if (info->signals & SerialSignal_DTR)
		val |= BIT3;
	else
		val &= ~BIT3;
	if (info->signals & SerialSignal_RTS)
		val |= BIT2;
	else
		val &= ~BIT2;
	wr_reg8(info, VCR, val);
}
