op_ld_reg16_imm(uint32_t op, const struct opinfo *oi)
{
	long val = get_imm16();
	long reg = (op >> 4) & 3;

	reg += reg > 2;
	DPRINTF(" %s  %s, 0x%04lx", oi->name, regnamech16[reg], val);
	REGS16_W(gbcpu_regs, reg, val);
}
