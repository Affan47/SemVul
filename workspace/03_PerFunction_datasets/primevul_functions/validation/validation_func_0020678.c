static void pop_callee_regs(u8 **pprog, bool *callee_regs_used)
{
	u8 *prog = *pprog;
	int cnt = 0;

	if (callee_regs_used[3])
		EMIT2(0x41, 0x5F);
	if (callee_regs_used[2])
		EMIT2(0x41, 0x5E);
	if (callee_regs_used[1])
		EMIT2(0x41, 0x5D);
	if (callee_regs_used[0])
		EMIT1(0x5B);
	*pprog = prog;
}
