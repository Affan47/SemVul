virt_to_phys_or_null_size(void *va, unsigned long size)
{
	bool bad_size;

	if (!va)
		return 0;

	if (virt_addr_valid(va))
		return virt_to_phys(va);


	bad_size = size > PAGE_SIZE || !is_power_of_2(size);

	WARN_ON(!IS_ALIGNED((unsigned long)va, size) || bad_size);

	return slow_virt_to_phys(va);
}
