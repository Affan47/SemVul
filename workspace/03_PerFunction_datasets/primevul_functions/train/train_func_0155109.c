static bool mmio_info_in_cache(struct kvm_vcpu *vcpu, u64 addr, bool direct)
{


	if (mmu_is_nested(vcpu))
		return false;

	if (direct)
		return vcpu_match_mmio_gpa(vcpu, addr);

	return vcpu_match_mmio_gva(vcpu, addr);
}
