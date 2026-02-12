static void apic_sync_pv_eoi_from_guest(struct kvm_vcpu *vcpu,
					struct kvm_lapic *apic)
{
	int vector;


	BUG_ON(!pv_eoi_enabled(vcpu));

	if (pv_eoi_test_and_clr_pending(vcpu))
		return;
	vector = apic_set_eoi(apic);
	trace_kvm_pv_eoi(apic, vector);
}
