static long ioctl_memcpy(struct fsl_hv_ioctl_memcpy __user *p)
{
	struct fsl_hv_ioctl_memcpy param;

	struct page **pages = NULL;
	void *sg_list_unaligned = NULL;
	struct fh_sg_list *sg_list = NULL;

	unsigned int num_pages;
	unsigned long lb_offset;

	unsigned int i;
	long ret = 0;
	int num_pinned;
	phys_addr_t remote_paddr;
	uint32_t count;


	if (copy_from_user(&param, p, sizeof(struct fsl_hv_ioctl_memcpy)))
		return -EFAULT;


	if ((param.source == -1) == (param.target == -1))
		return -EINVAL;


	lb_offset = param.local_vaddr & (PAGE_SIZE - 1);
	num_pages = (param.count + lb_offset + PAGE_SIZE - 1) >> PAGE_SHIFT;


	pages = kcalloc(num_pages, sizeof(struct page *), GFP_KERNEL);
	if (!pages) {
		pr_debug("fsl-hv: could not allocate page list\n");
		return -ENOMEM;
	}


	sg_list_unaligned = kmalloc(num_pages * sizeof(struct fh_sg_list) +
		sizeof(struct fh_sg_list) - 1, GFP_KERNEL);
	if (!sg_list_unaligned) {
		pr_debug("fsl-hv: could not allocate S/G list\n");
		ret = -ENOMEM;
		goto exit;
	}
	sg_list = PTR_ALIGN(sg_list_unaligned, sizeof(struct fh_sg_list));


	num_pinned = get_user_pages_fast(param.local_vaddr - lb_offset,
		num_pages, param.source != -1 ? FOLL_WRITE : 0, pages);

	if (num_pinned != num_pages) {

		pr_debug("fsl-hv: could not lock source buffer\n");
		ret = (num_pinned < 0) ? num_pinned : -EFAULT;
		goto exit;
	}


	if (param.source == -1) {
		sg_list[0].source = page_to_phys(pages[0]) + lb_offset;
		sg_list[0].target = param.remote_paddr;
	} else {
		sg_list[0].source = param.remote_paddr;
		sg_list[0].target = page_to_phys(pages[0]) + lb_offset;
	}
	sg_list[0].size = min_t(uint64_t, param.count, PAGE_SIZE - lb_offset);

	remote_paddr = param.remote_paddr + sg_list[0].size;
	count = param.count - sg_list[0].size;

	for (i = 1; i < num_pages; i++) {
		if (param.source == -1) {

			sg_list[i].source = page_to_phys(pages[i]);
			sg_list[i].target = remote_paddr;
		} else {

			sg_list[i].source = remote_paddr;
			sg_list[i].target = page_to_phys(pages[i]);
		}
		sg_list[i].size = min_t(uint64_t, count, PAGE_SIZE);

		remote_paddr += sg_list[i].size;
		count -= sg_list[i].size;
	}

	param.ret = fh_partition_memcpy(param.source, param.target,
		virt_to_phys(sg_list), num_pages);

exit:
	if (pages) {
		for (i = 0; i < num_pages; i++)
			if (pages[i])
				put_page(pages[i]);
	}

	kfree(sg_list_unaligned);
	kfree(pages);

	if (!ret)
		if (copy_to_user(&p->ret, &param.ret, sizeof(__u32)))
			return -EFAULT;

	return ret;
}
