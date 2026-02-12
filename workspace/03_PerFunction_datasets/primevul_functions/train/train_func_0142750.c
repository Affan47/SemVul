int get_user_pages_fast(unsigned long start, int nr_pages,
			unsigned int gup_flags, struct page **pages)
{


	if (WARN_ON_ONCE(gup_flags & FOLL_PIN))
		return -EINVAL;


	gup_flags |= FOLL_GET;
	return internal_get_user_pages_fast(start, nr_pages, gup_flags, pages);
}
