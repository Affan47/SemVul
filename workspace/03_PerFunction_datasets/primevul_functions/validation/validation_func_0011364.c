static int __vcpu_run(struct kvm_vcpu *vcpu)
{
	int rc, exit_reason;
	struct sie_page *sie_page = (struct sie_page *)vcpu->arch.sie_block;


	vcpu->srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);

	do {
		rc = vcpu_pre_run(vcpu);
		if (rc)
			break;

		srcu_read_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);


		local_irq_disable();
		guest_enter_irqoff();
		__disable_cpu_timer_accounting(vcpu);
		local_irq_enable();
		if (kvm_s390_pv_cpu_is_protected(vcpu)) {
			memcpy(sie_page->pv_grregs,
			       vcpu->run->s.regs.gprs,
			       sizeof(sie_page->pv_grregs));
		}
		exit_reason = sie64a(vcpu->arch.sie_block,
				     vcpu->run->s.regs.gprs);
		if (kvm_s390_pv_cpu_is_protected(vcpu)) {
			memcpy(vcpu->run->s.regs.gprs,
			       sie_page->pv_grregs,
			       sizeof(sie_page->pv_grregs));


			if (vcpu->arch.sie_block->icptcode == ICPT_PV_INSTR ||
			    vcpu->arch.sie_block->icptcode == ICPT_PV_PREF) {
				vcpu->arch.sie_block->gpsw.mask &= ~PSW_INT_MASK;
			}
		}
		local_irq_disable();
		__enable_cpu_timer_accounting(vcpu);
		guest_exit_irqoff();
		local_irq_enable();
		vcpu->srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);

		rc = vcpu_post_run(vcpu, exit_reason);
	} while (!signal_pending(current) && !guestdbg_exit_pending(vcpu) && !rc);

	srcu_read_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	return rc;
}
