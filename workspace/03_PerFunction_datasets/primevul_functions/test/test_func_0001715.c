static void nested_svm_transition_tlb_flush(struct kvm_vcpu *vcpu)
{


	kvm_make_request(KVM_REQ_MMU_SYNC, vcpu);
	kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
}
