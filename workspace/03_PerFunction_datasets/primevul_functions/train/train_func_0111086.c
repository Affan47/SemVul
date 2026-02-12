static int fib6_dump_node(struct fib6_walker *w)
{
	int res;
	struct fib6_info *rt;

	for_each_fib6_walker_rt(w) {
		res = rt6_dump_route(rt, w->args, w->skip_in_node);
		if (res >= 0) {

			w->leaf = rt;


			w->skip_in_node += res;

			return 1;
		}
		w->skip_in_node = 0;


		if (rt->fib6_nsiblings)
			rt = list_last_entry(&rt->fib6_siblings,
					     struct fib6_info,
					     fib6_siblings);
	}
	w->leaf = NULL;
	return 0;
}
