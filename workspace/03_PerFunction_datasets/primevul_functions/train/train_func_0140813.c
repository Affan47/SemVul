void kvm_inc_notifier_count(struct kvm *kvm, unsigned long start,
				   unsigned long end)
{


	kvm->mmu_notifier_count++;
	if (likely(kvm->mmu_notifier_count == 1)) {
		kvm->mmu_notifier_range_start = start;
		kvm->mmu_notifier_range_end = end;
	} else {


		kvm->mmu_notifier_range_start =
			min(kvm->mmu_notifier_range_start, start);
		kvm->mmu_notifier_range_end =
			max(kvm->mmu_notifier_range_end, end);
	}
}
