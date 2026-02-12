static inline bool pt_output_base_valid(struct kvm_vcpu *vcpu, u64 base)
{

	return kvm_vcpu_is_legal_aligned_gpa(vcpu, base, 128);
}
