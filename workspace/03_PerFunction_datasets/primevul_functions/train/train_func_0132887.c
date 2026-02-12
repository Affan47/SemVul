static bool pv_eoi_test_and_clr_pending(struct kvm_vcpu *vcpu)
{
	u8 val;

	if (pv_eoi_get_user(vcpu, &val) < 0)
		return false;

	val &= KVM_PV_EOI_ENABLED;

	if (val && pv_eoi_put_user(vcpu, KVM_PV_EOI_DISABLED) < 0)
		return false;


	__clear_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->arch.apic_attention);

	return val;
}
