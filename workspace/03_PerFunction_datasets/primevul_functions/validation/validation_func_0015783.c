static int kvm_mmu_notifier_clear_young(struct mmu_notifier *mn,
					struct mm_struct *mm,
					unsigned long start,
					unsigned long end)
{
	trace_kvm_age_hva(start, end);


	return kvm_handle_hva_range_no_flush(mn, start, end, kvm_age_gfn);
}
