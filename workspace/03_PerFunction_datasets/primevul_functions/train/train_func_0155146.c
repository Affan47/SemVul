static bool guest_can_use_gbpages(struct kvm_vcpu *vcpu)
{


	return tdp_enabled ? boot_cpu_has(X86_FEATURE_GBPAGES) :
			     guest_cpuid_has(vcpu, X86_FEATURE_GBPAGES);
}
