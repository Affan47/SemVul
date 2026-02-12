static bool svm_apic_init_signal_blocked(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);


	return !gif_set(svm) ||
		   (svm->vmcb->control.intercept & (1ULL << INTERCEPT_INIT));
}
