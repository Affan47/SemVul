static void kvm_set_mmio_spte_mask(void)
{
	u64 mask;
	int maxphyaddr = boot_cpu_data.x86_phys_bits;


	mask = 1ull << 51;


	mask |= 1ull;


	if (IS_ENABLED(CONFIG_X86_64) && maxphyaddr == 52)
		mask &= ~1ull;

	kvm_mmu_set_mmio_spte_mask(mask, mask);
}
