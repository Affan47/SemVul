void kvm_apic_write_nodecode(struct kvm_vcpu *vcpu, u32 offset)
{
	u32 val = kvm_lapic_get_reg(vcpu->arch.apic, offset);


	kvm_lapic_reg_write(vcpu->arch.apic, offset, val);
}
