static int visit_insn(int t, int insn_cnt, struct bpf_verifier_env *env)
{
	struct bpf_insn *insns = env->prog->insnsi;
	int ret;

	if (bpf_pseudo_func(insns + t))
		return visit_func_call_insn(t, insn_cnt, insns, env, true);


	if (BPF_CLASS(insns[t].code) != BPF_JMP &&
	    BPF_CLASS(insns[t].code) != BPF_JMP32)
		return push_insn(t, t + 1, FALLTHROUGH, env, false);

	switch (BPF_OP(insns[t].code)) {
	case BPF_EXIT:
		return DONE_EXPLORING;

	case BPF_CALL:
		if (insns[t].imm == BPF_FUNC_timer_set_callback)


			init_explored_state(env, t);
		return visit_func_call_insn(t, insn_cnt, insns, env,
					    insns[t].src_reg == BPF_PSEUDO_CALL);

	case BPF_JA:
		if (BPF_SRC(insns[t].code) != BPF_K)
			return -EINVAL;


		ret = push_insn(t, t + insns[t].off + 1, FALLTHROUGH, env,
				true);
		if (ret)
			return ret;


		init_explored_state(env, t + insns[t].off + 1);


		if (t + 1 < insn_cnt)
			init_explored_state(env, t + 1);

		return ret;

	default:

		init_explored_state(env, t);
		ret = push_insn(t, t + 1, FALLTHROUGH, env, true);
		if (ret)
			return ret;

		return push_insn(t, t + insns[t].off + 1, BRANCH, env, true);
	}
}
