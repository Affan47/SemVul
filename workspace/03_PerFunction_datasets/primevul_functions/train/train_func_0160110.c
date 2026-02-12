static void fill_sig_info_pkey(int si_signo, int si_code, siginfo_t *info,
		u32 *pkey)
{

	if (!boot_cpu_has(X86_FEATURE_OSPKE))
		return;


	if ((si_code != SEGV_PKUERR) || (si_signo != SIGSEGV))
		return;


	if (!pkey) {
		WARN_ONCE(1, "PKU fault with no VMA passed in");
		info->si_pkey = 0;
		return;
	}


	info->si_pkey = *pkey;
}
