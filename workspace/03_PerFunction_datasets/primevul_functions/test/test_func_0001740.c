void nested_vmcb02_compute_g_pat(struct vcpu_svm *svm)
{
	if (!svm->nested.vmcb02.ptr)
		return;


	svm->nested.vmcb02.ptr->save.g_pat = svm->vmcb01.ptr->save.g_pat;
}
