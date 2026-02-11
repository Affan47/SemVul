check_prev_add(struct task_struct *curr, struct held_lock *prev,
	       struct held_lock *next, int distance, int trylock_loop)
{
	struct lock_list *entry;
	int ret;
	struct lock_list this;
	struct lock_list *uninitialized_var(target_entry);


	static struct stack_trace trace;


	this.class = hlock_class(next);
	this.parent = NULL;
	ret = check_noncircular(&this, hlock_class(prev), &target_entry);
	if (unlikely(!ret))
		return print_circular_bug(&this, target_entry, next, prev);
	else if (unlikely(ret < 0))
		return print_bfs_bug(ret);

	if (!check_prev_add_irq(curr, prev, next))
		return 0;


	if (next->read == 2 || prev->read == 2)
		return 1;


	list_for_each_entry(entry, &hlock_class(prev)->locks_after, entry) {
		if (entry->class == hlock_class(next)) {
			if (distance == 1)
				entry->distance = 1;
			return 2;
		}
	}

	if (!trylock_loop && !save_trace(&trace))
		return 0;


	ret = add_lock_to_list(hlock_class(prev), hlock_class(next),
			       &hlock_class(prev)->locks_after,
			       next->acquire_ip, distance, &trace);

	if (!ret)
		return 0;

	ret = add_lock_to_list(hlock_class(next), hlock_class(prev),
			       &hlock_class(next)->locks_before,
			       next->acquire_ip, distance, &trace);
	if (!ret)
		return 0;


	if (verbose(hlock_class(prev)) || verbose(hlock_class(next))) {
		graph_unlock();
		printk("\n new dependency: ");
		print_lock_name(hlock_class(prev));
		printk(" => ");
		print_lock_name(hlock_class(next));
		printk("\n");
		dump_stack();
		return graph_lock();
	}
	return 1;
}
