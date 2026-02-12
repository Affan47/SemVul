static struct btf *find_kfunc_desc_btf(struct bpf_verifier_env *env,
				       u32 func_id, s16 offset,
				       struct module **btf_modp)
{
	if (offset) {
		if (offset < 0) {


			verbose(env, "negative offset disallowed for kernel module function call\n");
			return ERR_PTR(-EINVAL);
		}

		return __find_kfunc_desc_btf(env, offset, btf_modp);
	}
	return btf_vmlinux ?: ERR_PTR(-ENOENT);
}
