static int handle_encls(struct kvm_vcpu *vcpu)
{


	kvm_queue_exception(vcpu, UD_VECTOR);
	return 1;
}
