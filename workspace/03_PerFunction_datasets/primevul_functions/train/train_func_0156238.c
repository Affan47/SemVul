static void enable_irq_window(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);


	if (vgif_enabled(svm) || gif_set(svm)) {


		svm_toggle_avic_for_irq_window(vcpu, false);
		svm_set_vintr(svm);
	}
}
