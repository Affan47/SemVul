vb2_vmalloc_get_userptr(void *alloc_ctx, unsigned long vaddr,
				     unsigned long size,
				     enum dma_data_direction dma_dir)
{
	struct vb2_vmalloc_buf *buf;
	struct frame_vector *vec;
	int n_pages, offset, i;

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return NULL;

	buf->dma_dir = dma_dir;
	offset = vaddr & ~PAGE_MASK;
	buf->size = size;
	vec = vb2_create_framevec(vaddr, size, dma_dir == DMA_FROM_DEVICE);
	if (IS_ERR(vec))
		goto fail_pfnvec_create;
	buf->vec = vec;
	n_pages = frame_vector_count(vec);
	if (frame_vector_to_pages(vec) < 0) {
		unsigned long *nums = frame_vector_pfns(vec);


		for (i = 1; i < n_pages; i++)
			if (nums[i-1] + 1 != nums[i])
				goto fail_map;
		buf->vaddr = (__force void *)
				ioremap_nocache(nums[0] << PAGE_SHIFT, size);
	} else {
		buf->vaddr = vm_map_ram(frame_vector_pages(vec), n_pages, -1,
					PAGE_KERNEL);
	}

	if (!buf->vaddr)
		goto fail_map;
	buf->vaddr += offset;
	return buf;

fail_map:
	vb2_destroy_framevec(vec);
fail_pfnvec_create:
	kfree(buf);

	return NULL;
}
