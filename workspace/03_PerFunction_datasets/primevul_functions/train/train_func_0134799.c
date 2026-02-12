static long hugetlbfs_fallocate(struct file *file, int mode, loff_t offset,
				loff_t len)
{
	struct inode *inode = file_inode(file);
	struct address_space *mapping = inode->i_mapping;
	struct hstate *h = hstate_inode(inode);
	struct vm_area_struct pseudo_vma;
	struct mm_struct *mm = current->mm;
	loff_t hpage_size = huge_page_size(h);
	unsigned long hpage_shift = huge_page_shift(h);
	pgoff_t start, index, end;
	int error;
	u32 hash;

	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;

	if (mode & FALLOC_FL_PUNCH_HOLE)
		return hugetlbfs_punch_hole(inode, offset, len);


	start = offset >> hpage_shift;
	end = (offset + len + hpage_size - 1) >> hpage_shift;

	mutex_lock(&inode->i_mutex);


	error = inode_newsize_ok(inode, offset + len);
	if (error)
		goto out;


	memset(&pseudo_vma, 0, sizeof(struct vm_area_struct));
	pseudo_vma.vm_flags = (VM_HUGETLB | VM_MAYSHARE | VM_SHARED);
	pseudo_vma.vm_file = file;

	for (index = start; index < end; index++) {


		struct page *page;
		unsigned long addr;
		int avoid_reserve = 0;

		cond_resched();


		if (signal_pending(current)) {
			error = -EINTR;
			break;
		}


		hugetlb_set_vma_policy(&pseudo_vma, inode, index);


		addr = index * hpage_size;


		hash = hugetlb_fault_mutex_hash(h, mm, &pseudo_vma, mapping,
						index, addr);
		mutex_lock(&hugetlb_fault_mutex_table[hash]);


		page = find_get_page(mapping, index);
		if (page) {
			put_page(page);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			hugetlb_drop_vma_policy(&pseudo_vma);
			continue;
		}


		page = alloc_huge_page(&pseudo_vma, addr, avoid_reserve);
		hugetlb_drop_vma_policy(&pseudo_vma);
		if (IS_ERR(page)) {
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			error = PTR_ERR(page);
			goto out;
		}
		clear_huge_page(page, addr, pages_per_huge_page(h));
		__SetPageUptodate(page);
		error = huge_add_to_page_cache(page, mapping, index);
		if (unlikely(error)) {
			put_page(page);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			goto out;
		}

		mutex_unlock(&hugetlb_fault_mutex_table[hash]);


		put_page(page);
		unlock_page(page);
	}

	if (!(mode & FALLOC_FL_KEEP_SIZE) && offset + len > inode->i_size)
		i_size_write(inode, offset + len);
	inode->i_ctime = CURRENT_TIME;
out:
	mutex_unlock(&inode->i_mutex);
	return error;
}
