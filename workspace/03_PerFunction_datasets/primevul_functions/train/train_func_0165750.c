static int handle_rmode_exception(struct kvm_vcpu *vcpu,
				  int vec, u32 err_code)
{


	if (((vec == GP_VECTOR) || (vec == SS_VECTOR)) && err_code == 0)
		if (emulate_instruction(vcpu, NULL, 0, 0, 0) == EMULATE_DONE)
			return 1;


	switch (vec) {
	case DB_VECTOR:
		if (vcpu->guest_debug &
		    (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP))
			return 0;
		kvm_queue_exception(vcpu, vec);
		return 1;
	case BP_VECTOR:
		if (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			return 0;

	case DE_VECTOR:
	case OF_VECTOR:
	case BR_VECTOR:
	case UD_VECTOR:
	case DF_VECTOR:
	case SS_VECTOR:
	case GP_VECTOR:
	case MF_VECTOR:
		kvm_queue_exception(vcpu, vec);
		return 1;
	}
	return 0;
}
