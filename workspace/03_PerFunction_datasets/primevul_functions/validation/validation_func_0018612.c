static int nested_svm_intercept_db(struct vcpu_svm *svm)
{
	unsigned long dr6;


	if (!svm->nmi_singlestep)
		return NESTED_EXIT_DONE;


	if (kvm_get_dr(&svm->vcpu, 6, &dr6))
		return NESTED_EXIT_DONE;
	if (!(dr6 & DR6_BS))
		return NESTED_EXIT_DONE;


	if (svm->nmi_singlestep_guest_rflags & X86_EFLAGS_TF) {
		disable_nmi_singlestep(svm);
		return NESTED_EXIT_DONE;
	}


	return NESTED_EXIT_HOST;
}
