static inline void apic_set_isr(int vec, struct kvm_lapic *apic)
{
	struct kvm_vcpu *vcpu;

	if (__apic_test_and_set_vector(vec, apic->regs + APIC_ISR))
		return;

	vcpu = apic->vcpu;


	if (unlikely(vcpu->arch.apicv_active))
		static_call_cond(kvm_x86_hwapic_isr_update)(vcpu, vec);
	else {
		++apic->isr_count;
		BUG_ON(apic->isr_count > MAX_APIC_VECTOR);


		apic->highest_isr_cache = vec;
	}
}
