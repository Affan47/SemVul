static int emit_bpf_dispatcher(u8 **pprog, int a, int b, s64 *progs)
{
	u8 *jg_reloc, *prog = *pprog;
	int pivot, err, jg_bytes = 1, cnt = 0;
	s64 jg_offset;

	if (a == b) {


		EMIT1(add_1mod(0x48, BPF_REG_3));
		if (!is_simm32(progs[a]))
			return -1;
		EMIT2_off32(0x81, add_1reg(0xF8, BPF_REG_3),
			    progs[a]);
		err = emit_cond_near_jump(&prog,
					  (void *)progs[a], prog,
					  X86_JE);
		if (err)
			return err;

		err = emit_fallback_jump(&prog);
		if (err)
			return err;

		*pprog = prog;
		return 0;
	}


	pivot = (b - a) / 2;
	EMIT1(add_1mod(0x48, BPF_REG_3));
	if (!is_simm32(progs[a + pivot]))
		return -1;
	EMIT2_off32(0x81, add_1reg(0xF8, BPF_REG_3), progs[a + pivot]);

	if (pivot > 2) {

		jg_bytes = 4;
		EMIT2_off32(0x0F, X86_JG + 0x10, 0);
	} else {
		EMIT2(X86_JG, 0);
	}
	jg_reloc = prog;

	err = emit_bpf_dispatcher(&prog, a, a + pivot,
				  progs);
	if (err)
		return err;


	emit_align(&prog, 16);
	jg_offset = prog - jg_reloc;
	emit_code(jg_reloc - jg_bytes, jg_offset, jg_bytes);

	err = emit_bpf_dispatcher(&prog, a + pivot + 1,
				  b, progs);
	if (err)
		return err;

	*pprog = prog;
	return 0;
}
