debug_seq_show(struct seq_file *f, void *data)
{
	struct closure *cl;
	spin_lock_irq(&closure_list_lock);

	list_for_each_entry(cl, &closure_list, all) {
		int r = atomic_read(&cl->remaining);

		seq_printf(f, "%p: %pF -> %pf p %p r %i ",
			   cl, (void *) cl->ip, cl->fn, cl->parent,
			   r & CLOSURE_REMAINING_MASK);

		seq_printf(f, "%s%s%s%s\n",
			   test_bit(WORK_STRUCT_PENDING_BIT,
				    work_data_bits(&cl->work)) ? "Q" : "",
			   r & CLOSURE_RUNNING	? "R" : "",
			   r & CLOSURE_STACK	? "S" : "",
			   r & CLOSURE_SLEEPING	? "Sl" : "");

		if (r & CLOSURE_WAITING)
			seq_printf(f, " W %pF\n",
				   (void *) cl->waiting_on);

		seq_printf(f, "\n");
	}

	spin_unlock_irq(&closure_list_lock);
	return 0;
}
