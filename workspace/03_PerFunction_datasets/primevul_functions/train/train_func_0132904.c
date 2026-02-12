void kvm_apic_update_apicv(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	if (vcpu->arch.apicv_active) {

		apic->irr_pending = true;
		apic->isr_count = 1;
	} else {


		apic->isr_count = count_vectors(apic->regs + APIC_ISR);
	}
}
