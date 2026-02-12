static int kvm_lapic_msr_write(struct kvm_lapic *apic, u32 reg, u64 data)
{


	if (reg == APIC_ICR)
		return kvm_x2apic_icr_write(apic, data);

	return kvm_lapic_reg_write(apic, reg, (u32)data);
}
