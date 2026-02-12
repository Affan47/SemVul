static inline bool FNAME(is_last_gpte)(struct kvm_mmu *mmu,
				       unsigned int level, unsigned int gpte)
{


#if PTTYPE == 32


	gpte &= level - (PT32_ROOT_LEVEL + mmu->mmu_role.ext.cr4_pse);
#endif


	gpte |= level - PG_LEVEL_4K - 1;

	return gpte & PT_PAGE_SIZE_MASK;
}
