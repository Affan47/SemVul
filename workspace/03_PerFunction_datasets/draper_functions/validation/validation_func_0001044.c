apic_mmio_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this,
			    gpa_t address, int len, const void *data)
{
	struct kvm_lapic *apic = to_lapic(this);
	unsigned int offset = address - apic->base_address;
	u32 val;

	if (!apic_mmio_in_range(apic, address))
		return -EOPNOTSUPP;


	if (len != 4 || (offset & 0xf)) {

		apic_debug("apic write: bad size=%d %lx\n", len, (long)address);
		return 0;
	}

	val = *(u32*)data;


	if (offset != APIC_EOI)
		apic_debug("%s: offset 0x%x with length 0x%x, and value is "
			   "0x%x\n", __func__, offset, len, val);

	apic_reg_write(apic, offset & 0xff0, val);

	return 0;
}
