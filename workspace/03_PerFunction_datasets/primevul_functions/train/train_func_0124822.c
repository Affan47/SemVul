u64 kvm_get_arch_capabilities(void)
{
	u64 data;

	rdmsrl_safe(MSR_IA32_ARCH_CAPABILITIES, &data);


	if (l1tf_vmx_mitigation != VMENTER_L1D_FLUSH_NEVER)
		data |= ARCH_CAP_SKIP_VMENTRY_L1DFLUSH;

	return data;
}
