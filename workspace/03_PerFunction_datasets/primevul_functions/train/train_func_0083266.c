get_futex_key(u32 __user *uaddr, int fshared, union futex_key *key, int rw)
{
	unsigned long address = (unsigned long)uaddr;
	struct mm_struct *mm = current->mm;
	struct page *page;
	struct address_space *mapping;
	int err, ro = 0;


	key->both.offset = address % PAGE_SIZE;
	if (unlikely((address % sizeof(u32)) != 0))
		return -EINVAL;
	address -= key->both.offset;

	if (unlikely(!access_ok(rw, uaddr, sizeof(u32))))
		return -EFAULT;

	if (unlikely(should_fail_futex(fshared)))
		return -EFAULT;


	if (!fshared) {
		key->private.mm = mm;
		key->private.address = address;
		get_futex_key_refs(key);
		return 0;
	}

again:

	if (unlikely(should_fail_futex(fshared)))
		return -EFAULT;

	err = get_user_pages_fast(address, 1, 1, &page);


	if (err == -EFAULT && rw == VERIFY_READ) {
		err = get_user_pages_fast(address, 1, 0, &page);
		ro = 1;
	}
	if (err < 0)
		return err;
	else
		err = 0;

	lock_page(page);


	mapping = compound_head(page)->mapping;
	if (!mapping) {
		int shmem_swizzled = PageSwapCache(page);
		unlock_page(page);
		put_page(page);
		if (shmem_swizzled)
			goto again;
		return -EFAULT;
	}


	if (PageAnon(page)) {


		if (unlikely(should_fail_futex(fshared)) || ro) {
			err = -EFAULT;
			goto out;
		}

		key->both.offset |= FUT_OFF_MMSHARED;
		key->private.mm = mm;
		key->private.address = address;
	} else {
		key->both.offset |= FUT_OFF_INODE;
		key->shared.inode = mapping->host;
		key->shared.pgoff = basepage_index(page);
	}

	get_futex_key_refs(key);

out:
	unlock_page(page);
	put_page(page);
	return err;
}
