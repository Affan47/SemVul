static bool get_nx_auto_mode(void)
{

	return boot_cpu_has_bug(X86_BUG_ITLB_MULTIHIT) && !cpu_mitigations_off();
}
