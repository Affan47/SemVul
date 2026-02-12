int check_mem_reg(struct bpf_verifier_env *env, struct bpf_reg_state *reg,
		   u32 regno, u32 mem_size)
{
	if (register_is_null(reg))
		return 0;

	if (type_may_be_null(reg->type)) {


		const struct bpf_reg_state saved_reg = *reg;
		int rv;

		mark_ptr_not_null_reg(reg);
		rv = check_helper_mem_access(env, regno, mem_size, true, NULL);
		*reg = saved_reg;
		return rv;
	}

	return check_helper_mem_access(env, regno, mem_size, true, NULL);
}
