static int mmu_alloc_special_roots(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *mmu = vcpu->arch.mmu;
	bool need_pml5 = mmu->shadow_root_level > PT64_ROOT_4LEVEL;
	u64 *pml5_root = NULL;
	u64 *pml4_root = NULL;
	u64 *pae_root;


	if (mmu->direct_map || mmu->root_level >= PT64_ROOT_4LEVEL ||
	    mmu->shadow_root_level < PT64_ROOT_4LEVEL)
		return 0;


	if (mmu->pae_root && mmu->pml4_root && (!need_pml5 || mmu->pml5_root))
		return 0;


	if (WARN_ON_ONCE(!tdp_enabled || mmu->pae_root || mmu->pml4_root ||
			 (need_pml5 && mmu->pml5_root)))
		return -EIO;


	pae_root = (void *)get_zeroed_page(GFP_KERNEL_ACCOUNT);
	if (!pae_root)
		return -ENOMEM;

#ifdef CONFIG_X86_64
	pml4_root = (void *)get_zeroed_page(GFP_KERNEL_ACCOUNT);
	if (!pml4_root)
		goto err_pml4;

	if (need_pml5) {
		pml5_root = (void *)get_zeroed_page(GFP_KERNEL_ACCOUNT);
		if (!pml5_root)
			goto err_pml5;
	}
#endif

	mmu->pae_root = pae_root;
	mmu->pml4_root = pml4_root;
	mmu->pml5_root = pml5_root;

	return 0;

#ifdef CONFIG_X86_64
err_pml5:
	free_page((unsigned long)pml4_root);
err_pml4:
	free_page((unsigned long)pae_root);
	return -ENOMEM;
#endif
}
