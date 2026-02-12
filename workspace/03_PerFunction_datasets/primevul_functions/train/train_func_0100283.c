int __vm_enough_memory(long pages, int cap_sys_admin)
{
	unsigned long free, allowed;

	vm_acct_memory(pages);


	if (sysctl_overcommit_memory == OVERCOMMIT_ALWAYS)
		return 0;

	if (sysctl_overcommit_memory == OVERCOMMIT_GUESS) {
		unsigned long n;

		free = global_page_state(NR_FILE_PAGES);
		free += nr_swap_pages;


		free += global_page_state(NR_SLAB_RECLAIMABLE);


		if (!cap_sys_admin)
			free -= free / 32;

		if (free > pages)
			return 0;


		n = nr_free_pages();


		if (n <= totalreserve_pages)
			goto error;
		else
			n -= totalreserve_pages;


		if (!cap_sys_admin)
			n -= n / 32;
		free += n;

		if (free > pages)
			return 0;

		goto error;
	}

	allowed = (totalram_pages - hugetlb_total_pages())
	       	* sysctl_overcommit_ratio / 100;


	if (!cap_sys_admin)
		allowed -= allowed / 32;
	allowed += total_swap_pages;


	allowed -= current->mm->total_vm / 32;


	if (atomic_read(&vm_committed_space) < (long)allowed)
		return 0;
error:
	vm_unacct_memory(pages);

	return -ENOMEM;
}
