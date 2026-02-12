static inline void path_it_deinit(struct path_it *it)
{
	struct list_head *skip, *tmp;


	list_for_each_safe(skip, tmp, &it->skip_list)
		list_del_init(skip);
}
