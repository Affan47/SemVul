static void perf_mmap_close(struct vm_area_struct *vma)
{
	struct perf_event *event = vma->vm_file->private_data;
	struct perf_buffer *rb = ring_buffer_get(event);
	struct user_struct *mmap_user = rb->mmap_user;
	int mmap_locked = rb->mmap_locked;
	unsigned long size = perf_data_size(rb);
	bool detach_rest = false;

	if (event->pmu->event_unmapped)
		event->pmu->event_unmapped(event, vma->vm_mm);


	if (rb_has_aux(rb) && vma->vm_pgoff == rb->aux_pgoff &&
	    atomic_dec_and_mutex_lock(&rb->aux_mmap_count, &event->mmap_mutex)) {


		perf_pmu_output_stop(event);


		atomic_long_sub(rb->aux_nr_pages - rb->aux_mmap_locked, &mmap_user->locked_vm);
		atomic64_sub(rb->aux_mmap_locked, &vma->vm_mm->pinned_vm);


		rb_free_aux(rb);
		WARN_ON_ONCE(refcount_read(&rb->aux_refcount));

		mutex_unlock(&event->mmap_mutex);
	}

	if (atomic_dec_and_test(&rb->mmap_count))
		detach_rest = true;

	if (!atomic_dec_and_mutex_lock(&event->mmap_count, &event->mmap_mutex))
		goto out_put;

	ring_buffer_attach(event, NULL);
	mutex_unlock(&event->mmap_mutex);


	if (!detach_rest)
		goto out_put;


again:
	rcu_read_lock();
	list_for_each_entry_rcu(event, &rb->event_list, rb_entry) {
		if (!atomic_long_inc_not_zero(&event->refcount)) {


			continue;
		}
		rcu_read_unlock();

		mutex_lock(&event->mmap_mutex);


		if (event->rb == rb)
			ring_buffer_attach(event, NULL);

		mutex_unlock(&event->mmap_mutex);
		put_event(event);


		goto again;
	}
	rcu_read_unlock();


	atomic_long_sub((size >> PAGE_SHIFT) + 1 - mmap_locked,
			&mmap_user->locked_vm);
	atomic64_sub(mmap_locked, &vma->vm_mm->pinned_vm);
	free_uid(mmap_user);

out_put:
	ring_buffer_put(rb);
}
