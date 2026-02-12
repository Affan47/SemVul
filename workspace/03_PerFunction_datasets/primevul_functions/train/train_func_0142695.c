static int __gup_longterm_unlocked(unsigned long start, int nr_pages,
				   unsigned int gup_flags, struct page **pages)
{
	int ret;


	if (gup_flags & FOLL_LONGTERM) {
		down_read(&current->mm->mmap_sem);
		ret = __gup_longterm_locked(current, current->mm,
					    start, nr_pages,
					    pages, NULL, gup_flags);
		up_read(&current->mm->mmap_sem);
	} else {
		ret = get_user_pages_unlocked(start, nr_pages,
					      pages, gup_flags);
	}

	return ret;
}
