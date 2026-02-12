static void kvm_guest_apic_eoi_write(u32 reg, u32 val)
{


	if (__test_and_clear_bit(KVM_PV_EOI_BIT, this_cpu_ptr(&kvm_apic_eoi)))
		return;
	apic_write(APIC_EOI, APIC_EOI_ACK);
}
