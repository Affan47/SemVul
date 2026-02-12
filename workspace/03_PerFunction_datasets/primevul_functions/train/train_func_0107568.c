static unsigned int __bpf_prog_ret0_warn(const void *ctx,
					 const struct bpf_insn *insn)
{


	WARN_ON_ONCE(1);
	return 0;
}
