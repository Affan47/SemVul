static int inject_pending_event(struct kvm_vcpu *vcpu, bool req_int_win)
{
	int r;


	if (vcpu->arch.exception.injected)
		kvm_x86_ops->queue_exception(vcpu);


	else if (!vcpu->arch.exception.pending) {
		if (vcpu->arch.nmi_injected)
			kvm_x86_ops->set_nmi(vcpu);
		else if (vcpu->arch.interrupt.injected)
			kvm_x86_ops->set_irq(vcpu);
	}


	if (is_guest_mode(vcpu) && kvm_x86_ops->check_nested_events) {
		r = kvm_x86_ops->check_nested_events(vcpu, req_int_win);
		if (r != 0)
			return r;
	}


	if (vcpu->arch.exception.pending) {
		trace_kvm_inj_exception(vcpu->arch.exception.nr,
					vcpu->arch.exception.has_error_code,
					vcpu->arch.exception.error_code);

		WARN_ON_ONCE(vcpu->arch.exception.injected);
		vcpu->arch.exception.pending = false;
		vcpu->arch.exception.injected = true;

		if (exception_type(vcpu->arch.exception.nr) == EXCPT_FAULT)
			__kvm_set_rflags(vcpu, kvm_get_rflags(vcpu) |
					     X86_EFLAGS_RF);

		if (vcpu->arch.exception.nr == DB_VECTOR) {


			kvm_deliver_exception_payload(vcpu);
			if (vcpu->arch.dr7 & DR7_GD) {
				vcpu->arch.dr7 &= ~DR7_GD;
				kvm_update_dr7(vcpu);
			}
		}

		kvm_x86_ops->queue_exception(vcpu);
	}


	if (kvm_event_needs_reinjection(vcpu))
		return 0;

	if (vcpu->arch.smi_pending && !is_smm(vcpu) &&
	    kvm_x86_ops->smi_allowed(vcpu)) {
		vcpu->arch.smi_pending = false;
		++vcpu->arch.smi_count;
		enter_smm(vcpu);
	} else if (vcpu->arch.nmi_pending && kvm_x86_ops->nmi_allowed(vcpu)) {
		--vcpu->arch.nmi_pending;
		vcpu->arch.nmi_injected = true;
		kvm_x86_ops->set_nmi(vcpu);
	} else if (kvm_cpu_has_injectable_intr(vcpu)) {


		if (is_guest_mode(vcpu) && kvm_x86_ops->check_nested_events) {
			r = kvm_x86_ops->check_nested_events(vcpu, req_int_win);
			if (r != 0)
				return r;
		}
		if (kvm_x86_ops->interrupt_allowed(vcpu)) {
			kvm_queue_interrupt(vcpu, kvm_cpu_get_interrupt(vcpu),
					    false);
			kvm_x86_ops->set_irq(vcpu);
		}
	}

	return 0;
}
