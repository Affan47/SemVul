insn_uses(struct insn *insn, struct var_info **uses)
{
	unsigned long flags;
	int nr = 0;

	flags = insn_flags[insn->type];

	if (flags & USE_SRC)
		uses[nr++] = insn->src.reg.interval->var_info;

	if (flags & USE_DST)
		uses[nr++] = insn->dest.reg.interval->var_info;

	if (flags & USE_IDX_SRC)
		uses[nr++] = insn->src.index_reg.interval->var_info;

	if (flags & USE_IDX_DST)
		uses[nr++] = insn->dest.index_reg.interval->var_info;

	return nr;
}
