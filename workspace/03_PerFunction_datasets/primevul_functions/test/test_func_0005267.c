static struct bpf_verifier_state *push_async_cb(struct bpf_verifier_env *env,
						int insn_idx, int prev_insn_idx,
						int subprog)
{
	struct bpf_verifier_stack_elem *elem;
	struct bpf_func_state *frame;

	elem = kzalloc(sizeof(struct bpf_verifier_stack_elem), GFP_KERNEL);
	if (!elem)
		goto err;

	elem->insn_idx = insn_idx;
	elem->prev_insn_idx = prev_insn_idx;
	elem->next = env->head;
	elem->log_pos = env->log.len_used;
	env->head = elem;
	env->stack_size++;
	if (env->stack_size > BPF_COMPLEXITY_LIMIT_JMP_SEQ) {
		verbose(env,
			"The sequence of %d jumps is too complex for async cb.\n",
			env->stack_size);
		goto err;
	}


	elem->st.branches = 1;
	frame = kzalloc(sizeof(*frame), GFP_KERNEL);
	if (!frame)
		goto err;
	init_func_state(env, frame,
			BPF_MAIN_FUNC ,
			0 ,
			subprog );
	elem->st.frame[0] = frame;
	return &elem->st;
err:
	free_verifier_state(env->cur_state, true);
	env->cur_state = NULL;

	while (!pop_stack(env, NULL, NULL, false));
	return NULL;
}
