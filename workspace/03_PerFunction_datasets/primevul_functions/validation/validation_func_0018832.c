static int svm_smi_allowed(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);


	if (!gif_set(svm))
		return 0;

	if (is_guest_mode(&svm->vcpu) &&
	    svm->nested.intercept & (1ULL << INTERCEPT_SMI)) {

		svm->vmcb->control.exit_code = SVM_EXIT_SMI;
		svm->nested.exit_required = true;
		return 0;
	}

	return 1;
}
