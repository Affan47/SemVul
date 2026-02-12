static void perf_event_addr_filters_apply(struct perf_event *event)
{
	struct perf_addr_filters_head *ifh = perf_event_addr_filters(event);
	struct task_struct *task = READ_ONCE(event->ctx->task);
	struct perf_addr_filter *filter;
	struct mm_struct *mm = NULL;
	unsigned int count = 0;
	unsigned long flags;


	if (task == TASK_TOMBSTONE)
		return;

	if (ifh->nr_file_filters) {
		mm = get_task_mm(event->ctx->task);
		if (!mm)
			goto restart;

		mmap_read_lock(mm);
	}

	raw_spin_lock_irqsave(&ifh->lock, flags);
	list_for_each_entry(filter, &ifh->list, entry) {
		if (filter->path.dentry) {


			event->addr_filter_ranges[count].start = 0;
			event->addr_filter_ranges[count].size = 0;

			perf_addr_filter_apply(filter, mm, &event->addr_filter_ranges[count]);
		} else {
			event->addr_filter_ranges[count].start = filter->offset;
			event->addr_filter_ranges[count].size  = filter->size;
		}

		count++;
	}

	event->addr_filters_gen++;
	raw_spin_unlock_irqrestore(&ifh->lock, flags);

	if (ifh->nr_file_filters) {
		mmap_read_unlock(mm);

		mmput(mm);
	}

restart:
	perf_event_stop(event, 1);
}
