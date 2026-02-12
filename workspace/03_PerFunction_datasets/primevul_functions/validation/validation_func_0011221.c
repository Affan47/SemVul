static void disable_cpu_timer_accounting(struct kvm_vcpu *vcpu)
{
	preempt_disable();
	__disable_cpu_timer_accounting(vcpu);
	preempt_enable();
}
