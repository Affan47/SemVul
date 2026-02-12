int kvm_arch_prepare_memory_region(struct kvm *kvm,
				   struct kvm_memory_slot *memslot,
				   const struct kvm_userspace_memory_region *mem,
				   enum kvm_mr_change change)
{


	if (mem->userspace_addr & 0xffffful)
		return -EINVAL;

	if (mem->memory_size & 0xffffful)
		return -EINVAL;

	if (mem->guest_phys_addr + mem->memory_size > kvm->arch.mem_limit)
		return -EINVAL;


	if (kvm_s390_pv_get_handle(kvm))
		return -EINVAL;
	return 0;
}
