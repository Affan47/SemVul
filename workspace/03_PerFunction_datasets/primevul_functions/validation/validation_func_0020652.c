static void emit_bpf_tail_call_indirect(u8 **pprog, bool *callee_regs_used,
					u32 stack_depth)
{
	int tcc_off = -4 - round_up(stack_depth, 8);
	u8 *prog = *pprog;
	int pop_bytes = 0;
	int off1 = 42;
	int off2 = 31;
	int off3 = 9;
	int cnt = 0;


	pop_bytes = get_pop_bytes(callee_regs_used);
	off1 += pop_bytes;
	off2 += pop_bytes;
	off3 += pop_bytes;

	if (stack_depth) {
		off1 += 7;
		off2 += 7;
		off3 += 7;
	}


	EMIT2(0x89, 0xD2);
	EMIT3(0x39, 0x56,
	      offsetof(struct bpf_array, map.max_entries));
#define OFFSET1 (off1 + RETPOLINE_RCX_BPF_JIT_SIZE)
	EMIT2(X86_JBE, OFFSET1);


	EMIT2_off32(0x8B, 0x85, tcc_off);
	EMIT3(0x83, 0xF8, MAX_TAIL_CALL_CNT);
#define OFFSET2 (off2 + RETPOLINE_RCX_BPF_JIT_SIZE)
	EMIT2(X86_JA, OFFSET2);
	EMIT3(0x83, 0xC0, 0x01);
	EMIT2_off32(0x89, 0x85, tcc_off);


	EMIT4_off32(0x48, 0x8B, 0x8C, 0xD6,
		    offsetof(struct bpf_array, ptrs));


	EMIT3(0x48, 0x85, 0xC9);
#define OFFSET3 (off3 + RETPOLINE_RCX_BPF_JIT_SIZE)
	EMIT2(X86_JE, OFFSET3);

	*pprog = prog;
	pop_callee_regs(pprog, callee_regs_used);
	prog = *pprog;

	EMIT1(0x58);
	if (stack_depth)
		EMIT3_off32(0x48, 0x81, 0xC4,
			    round_up(stack_depth, 8));


	EMIT4(0x48, 0x8B, 0x49,
	      offsetof(struct bpf_prog, bpf_func));
	EMIT4(0x48, 0x83, 0xC1,
	      X86_TAIL_CALL_OFFSET);


	RETPOLINE_RCX_BPF_JIT();


	*pprog = prog;
}
