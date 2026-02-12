static int handle_invd(struct kvm_vcpu *vcpu)
{

	return kvm_skip_emulated_instruction(vcpu);
}
