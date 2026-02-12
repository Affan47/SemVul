static void vmx_flush_tlb_gva(struct kvm_vcpu *vcpu, gva_t addr)
{


	vpid_sync_vcpu_addr(to_vmx(vcpu)->vpid, addr);
}
