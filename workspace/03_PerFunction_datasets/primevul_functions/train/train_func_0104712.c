static int prepare_func_exit(struct bpf_verifier_env *env, int *insn_idx)
{
	struct bpf_verifier_state *state = env->cur_state;
	struct bpf_func_state *caller, *callee;
	struct bpf_reg_state *r0;
	int err;

	callee = state->frame[state->curframe];
	r0 = &callee->regs[BPF_REG_0];
	if (r0->type == PTR_TO_STACK) {


		verbose(env, "cannot return stack pointer to the caller\n");
		return -EINVAL;
	}

	state->curframe--;
	caller = state->frame[state->curframe];
	if (callee->in_callback_fn) {

		struct tnum range = tnum_range(0, 1);

		if (r0->type != SCALAR_VALUE) {
			verbose(env, "R0 not a scalar value\n");
			return -EACCES;
		}
		if (!tnum_in(range, r0->var_off)) {
			verbose_invalid_scalar(env, r0, &range, "callback return", "R0");
			return -EINVAL;
		}
	} else {

		caller->regs[BPF_REG_0] = *r0;
	}


	err = copy_reference_state(caller, callee);
	if (err)
		return err;

	*insn_idx = callee->callsite + 1;
	if (env->log.level & BPF_LOG_LEVEL) {
		verbose(env, "returning from callee:\n");
		print_verifier_state(env, callee);
		verbose(env, "to caller at %d:\n", *insn_idx);
		print_verifier_state(env, caller);
	}

	free_func_state(callee);
	state->frame[state->curframe + 1] = NULL;
	return 0;
}
