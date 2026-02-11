kaiser_flush_tlb_on_return_to_user(void)
{
	if (this_cpu_has(X86_FEATURE_PCID))
		this_cpu_write(x86_cr3_pcid_user,
			X86_CR3_PCID_USER_FLUSH | KAISER_SHADOW_PGD_OFFSET);
}
