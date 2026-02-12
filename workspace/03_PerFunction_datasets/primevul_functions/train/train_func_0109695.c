static int __copy_insn(struct address_space *mapping, struct file *filp,
			void *insn, int nbytes, loff_t offset)
{
	struct page *page;


	if (mapping->a_ops->readpage)
		page = read_mapping_page(mapping, offset >> PAGE_SHIFT, filp);
	else
		page = shmem_read_mapping_page(mapping, offset >> PAGE_SHIFT);
	if (IS_ERR(page))
		return PTR_ERR(page);

	copy_from_page(page, offset, insn, nbytes);
	put_page(page);

	return 0;
}
