static bool handle_abnormal_pfn(struct kvm_vcpu *vcpu, struct kvm_page_fault *fault,
				unsigned int access, int *ret_val)
{

	if (unlikely(is_error_pfn(fault->pfn))) {
		*ret_val = kvm_handle_bad_page(vcpu, fault->gfn, fault->pfn);
		return true;
	}

	if (unlikely(!fault->slot)) {
		gva_t gva = fault->is_tdp ? 0 : fault->addr;

		vcpu_cache_mmio_info(vcpu, gva, fault->gfn,
				     access & shadow_mmio_access_mask);


		if (unlikely(!shadow_mmio_value) ||
		    unlikely(fault->gfn > kvm_mmu_max_gfn())) {
			*ret_val = RET_PF_EMULATE;
			return true;
		}
	}

	return false;
}
