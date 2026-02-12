void kvm_deliver_exception_payload(struct kvm_vcpu *vcpu)
{
	unsigned nr = vcpu->arch.exception.nr;
	bool has_payload = vcpu->arch.exception.has_payload;
	unsigned long payload = vcpu->arch.exception.payload;

	if (!has_payload)
		return;

	switch (nr) {
	case DB_VECTOR:


		vcpu->arch.dr6 &= ~DR_TRAP_BITS;


		vcpu->arch.dr6 |= DR6_RTM;
		vcpu->arch.dr6 |= payload;


		vcpu->arch.dr6 ^= payload & DR6_RTM;
		break;
	case PF_VECTOR:
		vcpu->arch.cr2 = payload;
		break;
	}

	vcpu->arch.exception.has_payload = false;
	vcpu->arch.exception.payload = 0;
}
