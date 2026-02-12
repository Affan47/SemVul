static int check_cfg(struct bpf_verifier_env *env)
{
	struct bpf_insn *insns = env->prog->insnsi;
	int insn_cnt = env->prog->len;
	int *insn_stack, *insn_state;
	int ret = 0;
	int i, t;

	insn_state = env->cfg.insn_state = kvcalloc(insn_cnt, sizeof(int), GFP_KERNEL);
	if (!insn_state)
		return -ENOMEM;

	insn_stack = env->cfg.insn_stack = kvcalloc(insn_cnt, sizeof(int), GFP_KERNEL);
	if (!insn_stack) {
		kvfree(insn_state);
		return -ENOMEM;
	}

	insn_state[0] = DISCOVERED;
	insn_stack[0] = 0;
	env->cfg.cur_stack = 1;

peek_stack:
	if (env->cfg.cur_stack == 0)
		goto check_state;
	t = insn_stack[env->cfg.cur_stack - 1];

	if (BPF_CLASS(insns[t].code) == BPF_JMP ||
	    BPF_CLASS(insns[t].code) == BPF_JMP32) {
		u8 opcode = BPF_OP(insns[t].code);

		if (opcode == BPF_EXIT) {
			goto mark_explored;
		} else if (opcode == BPF_CALL) {
			ret = push_insn(t, t + 1, FALLTHROUGH, env, false);
			if (ret == 1)
				goto peek_stack;
			else if (ret < 0)
				goto err_free;
			if (t + 1 < insn_cnt)
				init_explored_state(env, t + 1);
			if (insns[t].src_reg == BPF_PSEUDO_CALL) {
				init_explored_state(env, t);
				ret = push_insn(t, t + insns[t].imm + 1, BRANCH,
						env, false);
				if (ret == 1)
					goto peek_stack;
				else if (ret < 0)
					goto err_free;
			}
		} else if (opcode == BPF_JA) {
			if (BPF_SRC(insns[t].code) != BPF_K) {
				ret = -EINVAL;
				goto err_free;
			}

			ret = push_insn(t, t + insns[t].off + 1,
					FALLTHROUGH, env, true);
			if (ret == 1)
				goto peek_stack;
			else if (ret < 0)
				goto err_free;


			init_explored_state(env, t + insns[t].off + 1);


			if (t + 1 < insn_cnt)
				init_explored_state(env, t + 1);
		} else {

			init_explored_state(env, t);
			ret = push_insn(t, t + 1, FALLTHROUGH, env, true);
			if (ret == 1)
				goto peek_stack;
			else if (ret < 0)
				goto err_free;

			ret = push_insn(t, t + insns[t].off + 1, BRANCH, env, true);
			if (ret == 1)
				goto peek_stack;
			else if (ret < 0)
				goto err_free;
		}
	} else {


		ret = push_insn(t, t + 1, FALLTHROUGH, env, false);
		if (ret == 1)
			goto peek_stack;
		else if (ret < 0)
			goto err_free;
	}

mark_explored:
	insn_state[t] = EXPLORED;
	if (env->cfg.cur_stack-- <= 0) {
		verbose(env, "pop stack internal bug\n");
		ret = -EFAULT;
		goto err_free;
	}
	goto peek_stack;

check_state:
	for (i = 0; i < insn_cnt; i++) {
		if (insn_state[i] != EXPLORED) {
			verbose(env, "unreachable insn %d\n", i);
			ret = -EINVAL;
			goto err_free;
		}
	}
	ret = 0;

err_free:
	kvfree(insn_state);
	kvfree(insn_stack);
	env->cfg.insn_state = env->cfg.insn_stack = NULL;
	return ret;
}
