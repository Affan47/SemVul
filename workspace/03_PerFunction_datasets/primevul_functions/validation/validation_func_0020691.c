static int invoke_bpf_mod_ret(const struct btf_func_model *m, u8 **pprog,
			      struct bpf_tramp_progs *tp, int stack_size,
			      u8 **branches)
{
	u8 *prog = *pprog;
	int i, cnt = 0;


	emit_mov_imm32(&prog, false, BPF_REG_0, 0);
	emit_stx(&prog, BPF_DW, BPF_REG_FP, BPF_REG_0, -8);
	for (i = 0; i < tp->nr_progs; i++) {
		if (invoke_bpf_prog(m, &prog, tp->progs[i], stack_size, true))
			return -EINVAL;


		EMIT4(0x48, 0x83, 0x7d, 0xf8); EMIT1(0x00);


		branches[i] = prog;
		emit_nops(&prog, 4 + 2);
	}

	*pprog = prog;
	return 0;
}
