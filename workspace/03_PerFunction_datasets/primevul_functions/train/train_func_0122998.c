static int handle_rmode_exception(struct kvm_vcpu *vcpu,
				  int vec, u32 err_code)
{


	if (((vec == GP_VECTOR) || (vec == SS_VECTOR)) && err_code == 0) {
		if (kvm_emulate_instruction(vcpu, 0)) {
			if (vcpu->arch.halt_request) {
				vcpu->arch.halt_request = 0;
				return kvm_vcpu_halt(vcpu);
			}
			return 1;
		}
		return 0;
	}


	kvm_queue_exception(vcpu, vec);
	return 1;
}
