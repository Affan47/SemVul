static inline bool kvm_check_request(int req, struct kvm_vcpu *vcpu)
{
	if (kvm_test_request(req, vcpu)) {
		kvm_clear_request(req, vcpu);


		smp_mb__after_atomic();
		return true;
	} else {
		return false;
	}
}
