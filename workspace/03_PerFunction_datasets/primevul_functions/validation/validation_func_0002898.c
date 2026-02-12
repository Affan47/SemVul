static bool is_reg64(struct bpf_verifier_env *env, struct bpf_insn *insn,
		     u32 regno, struct bpf_reg_state *reg, enum reg_arg_type t)
{
	u8 code, class, op;

	code = insn->code;
	class = BPF_CLASS(code);
	op = BPF_OP(code);
	if (class == BPF_JMP) {


		if (op == BPF_EXIT)
			return true;
		if (op == BPF_CALL) {


			if (insn->src_reg == BPF_PSEUDO_CALL)
				return false;


			if (t == SRC_OP)
				return true;

			return false;
		}
	}

	if (class == BPF_ALU64 || class == BPF_JMP ||

	    (class == BPF_ALU && op == BPF_END && insn->imm == 64))
		return true;

	if (class == BPF_ALU || class == BPF_JMP32)
		return false;

	if (class == BPF_LDX) {
		if (t != SRC_OP)
			return BPF_SIZE(code) == BPF_DW;

		return true;
	}

	if (class == BPF_STX) {
		if (reg->type != SCALAR_VALUE)
			return true;
		return BPF_SIZE(code) == BPF_DW;
	}

	if (class == BPF_LD) {
		u8 mode = BPF_MODE(code);


		if (mode == BPF_IMM)
			return true;


		if (t != SRC_OP)
			return  false;


		if (regno == BPF_REG_6)
			return true;


		return true;
	}

	if (class == BPF_ST)

		return true;


	return true;
}
