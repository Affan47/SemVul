static int avic_handle_apic_id_update(struct kvm_vcpu *vcpu)
{
	u64 *old, *new;
	struct vcpu_svm *svm = to_svm(vcpu);
	u32 id = kvm_xapic_id(vcpu->arch.apic);

	if (vcpu->vcpu_id == id)
		return 0;

	old = avic_get_physical_id_entry(vcpu, vcpu->vcpu_id);
	new = avic_get_physical_id_entry(vcpu, id);
	if (!new || !old)
		return 1;


	*new = *old;
	*old = 0ULL;
	to_svm(vcpu)->avic_physical_id_cache = new;


	if (svm->ldr_reg)
		avic_handle_ldr_update(vcpu);

	return 0;
}
