static int delete_from_lru_cache(struct page *p)
{
	if (!isolate_lru_page(p)) {


		ClearPageActive(p);
		ClearPageUnevictable(p);


		mem_cgroup_uncharge(p);


		put_page(p);
		return 0;
	}
	return -EIO;
}
