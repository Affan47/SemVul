static void kvm_dec_notifier_count(struct kvm *kvm, unsigned long start,
				   unsigned long end)
{


	kvm->mmu_notifier_seq++;
	smp_wmb();


	kvm->mmu_notifier_count--;
}
