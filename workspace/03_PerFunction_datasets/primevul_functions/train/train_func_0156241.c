static inline void svm_enable_vintr(struct vcpu_svm *svm)
{
	struct vmcb_control_area *control;


	WARN_ON(kvm_vcpu_apicv_active(&svm->vcpu));


	control = &svm->vmcb->control;
	control->int_vector = 0x0;
	control->int_ctl &= ~V_INTR_PRIO_MASK;
	control->int_ctl |= V_IRQ_MASK |
		(( 0xf) << V_INTR_PRIO_SHIFT);
	mark_dirty(svm->vmcb, VMCB_INTR);
}
