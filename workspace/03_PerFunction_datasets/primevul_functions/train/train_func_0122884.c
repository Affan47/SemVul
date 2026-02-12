static int handle_apic_eoi_induced(struct kvm_vcpu *vcpu)
{
	unsigned long exit_qualification = vmx_get_exit_qual(vcpu);
	int vector = exit_qualification & 0xff;


	kvm_apic_set_eoi_accelerated(vcpu, vector);
	return 1;
}
