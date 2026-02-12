static u64 perf_virt_to_phys(u64 virt)
{
	u64 phys_addr = 0;
	struct page *p = NULL;

	if (!virt)
		return 0;

	if (virt >= TASK_SIZE) {

		if (virt_addr_valid((void *)(uintptr_t)virt) &&
		    !(virt >= VMALLOC_START && virt < VMALLOC_END))
			phys_addr = (u64)virt_to_phys((void *)(uintptr_t)virt);
	} else {


		if (current->mm != NULL) {
			pagefault_disable();
			if (get_user_page_fast_only(virt, 0, &p))
				phys_addr = page_to_phys(p) + virt % PAGE_SIZE;
			pagefault_enable();
		}

		if (p)
			put_page(p);
	}

	return phys_addr;
}
