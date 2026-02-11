__recover_probed_insn(kprobe_opcode_t *buf, unsigned long addr)
{
	struct kprobe *kp;
	unsigned long faddr;

	kp = get_kprobe((void *)addr);
	faddr = ftrace_location(addr);


	if (WARN_ON(faddr && faddr != addr))
		return 0UL;


	if (!kp && !faddr)
		return addr;


	memcpy(buf, (void *)addr, MAX_INSN_SIZE * sizeof(kprobe_opcode_t));
	if (faddr)
		memcpy(buf, ideal_nops[NOP_ATOMIC5], 5);
	else
		buf[0] = kp->opcode;
	return (unsigned long)buf;
}
