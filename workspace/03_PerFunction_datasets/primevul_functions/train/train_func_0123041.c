static inline int __hv_remote_flush_tlb_with_range(struct kvm *kvm,
		struct kvm_vcpu *vcpu, struct kvm_tlb_range *range)
{
	u64 ept_pointer = to_vmx(vcpu)->ept_pointer;


	if (range)
		return hyperv_flush_guest_mapping_range(ept_pointer & PAGE_MASK,
				kvm_fill_hv_flush_list_func, (void *)range);
	else
		return hyperv_flush_guest_mapping(ept_pointer & PAGE_MASK);
}
