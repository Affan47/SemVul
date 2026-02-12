static inline int kvm_mmu_get_tdp_level(struct kvm_vcpu *vcpu)
{

	if (tdp_root_level)
		return tdp_root_level;


	if (max_tdp_level == 5 && cpuid_maxphyaddr(vcpu) <= 48)
		return 4;

	return max_tdp_level;
}
