static long __get_user_pages_remote(struct task_struct *tsk,
				    struct mm_struct *mm,
				    unsigned long start, unsigned long nr_pages,
				    unsigned int gup_flags, struct page **pages,
				    struct vm_area_struct **vmas, int *locked)
{


	if (gup_flags & FOLL_LONGTERM) {
		if (WARN_ON_ONCE(locked))
			return -EINVAL;


		return __gup_longterm_locked(tsk, mm, start, nr_pages, pages,
					     vmas, gup_flags | FOLL_TOUCH |
					     FOLL_REMOTE);
	}

	return __get_user_pages_locked(tsk, mm, start, nr_pages, pages, vmas,
				       locked,
				       gup_flags | FOLL_TOUCH | FOLL_REMOTE);
}
