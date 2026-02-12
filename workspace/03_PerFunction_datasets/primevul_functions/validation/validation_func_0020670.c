static void emit_insn_suffix(u8 **pprog, u32 ptr_reg, u32 val_reg, int off)
{
	u8 *prog = *pprog;
	int cnt = 0;

	if (is_imm8(off)) {


		EMIT2(add_2reg(0x40, ptr_reg, val_reg), off);
	} else {

		EMIT1_off32(add_2reg(0x80, ptr_reg, val_reg), off);
	}
	*pprog = prog;
}
