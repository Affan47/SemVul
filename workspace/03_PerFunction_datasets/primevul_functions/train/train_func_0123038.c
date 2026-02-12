static void vmx_flush_tlb_guest(struct kvm_vcpu *vcpu)
{


	vpid_sync_context(to_vmx(vcpu)->vpid);
}
