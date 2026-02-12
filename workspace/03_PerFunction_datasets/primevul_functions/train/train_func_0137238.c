static u32 bpf_map_flags_retain_permanent(u32 flags)
{


	return flags & ~(BPF_F_RDONLY | BPF_F_WRONLY);
}
