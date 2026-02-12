static inline int kvm_vcpu_exiting_guest_mode(struct kvm_vcpu *vcpu)
{


	smp_mb__before_atomic();
	return cmpxchg(&vcpu->mode, IN_GUEST_MODE, EXITING_GUEST_MODE);
}
