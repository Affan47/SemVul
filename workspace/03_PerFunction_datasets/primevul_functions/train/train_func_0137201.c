static void *__bpf_map_area_alloc(u64 size, int numa_node, bool mmapable)
{


	const gfp_t gfp = __GFP_NOWARN | __GFP_ZERO | __GFP_ACCOUNT;
	unsigned int flags = 0;
	unsigned long align = 1;
	void *area;

	if (size >= SIZE_MAX)
		return NULL;


	if (mmapable) {
		BUG_ON(!PAGE_ALIGNED(size));
		align = SHMLBA;
		flags = VM_USERMAP;
	} else if (size <= (PAGE_SIZE << PAGE_ALLOC_COSTLY_ORDER)) {
		area = kmalloc_node(size, gfp | GFP_USER | __GFP_NORETRY,
				    numa_node);
		if (area != NULL)
			return area;
	}

	return __vmalloc_node_range(size, align, VMALLOC_START, VMALLOC_END,
			gfp | GFP_KERNEL | __GFP_RETRY_MAYFAIL, PAGE_KERNEL,
			flags, numa_node, __builtin_return_address(0));
}
