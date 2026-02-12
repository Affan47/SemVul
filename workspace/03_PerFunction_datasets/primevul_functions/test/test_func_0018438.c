void sev_vcpu_deliver_sipi_vector(struct kvm_vcpu *vcpu, u8 vector)
{
	struct vcpu_svm *svm = to_svm(vcpu);


	if (!svm->received_first_sipi) {
		svm->received_first_sipi = true;
		return;
	}


	if (!svm->ghcb)
		return;

	ghcb_set_sw_exit_info_2(svm->ghcb, 1);
}
