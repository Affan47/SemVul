int bpf_arch_text_poke(void *ip, enum bpf_text_poke_type t,
		       void *old_addr, void *new_addr)
{
	if (!is_kernel_text((long)ip) &&
	    !is_bpf_text_address((long)ip))

		return -EINVAL;

	return __bpf_arch_text_poke(ip, t, old_addr, new_addr, true);
}
