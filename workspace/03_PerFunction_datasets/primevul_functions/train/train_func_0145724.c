static noinline int eb_relocate_slow(struct i915_execbuffer *eb)
{
	struct drm_device *dev = &eb->i915->drm;
	bool have_copy = false;
	struct i915_vma *vma;
	int err = 0;

repeat:
	if (signal_pending(current)) {
		err = -ERESTARTSYS;
		goto out;
	}


	eb_reset_vmas(eb);
	mutex_unlock(&dev->struct_mutex);


	if (!err) {
		err = eb_prefault_relocations(eb);
	} else if (!have_copy) {
		err = eb_copy_relocations(eb);
		have_copy = err == 0;
	} else {
		cond_resched();
		err = 0;
	}
	if (err) {
		mutex_lock(&dev->struct_mutex);
		goto out;
	}


	flush_workqueue(eb->i915->mm.userptr_wq);

	err = i915_mutex_lock_interruptible(dev);
	if (err) {
		mutex_lock(&dev->struct_mutex);
		goto out;
	}


	err = eb_lookup_vmas(eb);
	if (err)
		goto err;

	GEM_BUG_ON(!eb->batch);

	list_for_each_entry(vma, &eb->relocs, reloc_link) {
		if (!have_copy) {
			pagefault_disable();
			err = eb_relocate_vma(eb, vma);
			pagefault_enable();
			if (err)
				goto repeat;
		} else {
			err = eb_relocate_vma_slow(eb, vma);
			if (err)
				goto err;
		}
	}


err:
	if (err == -EAGAIN)
		goto repeat;

out:
	if (have_copy) {
		const unsigned int count = eb->buffer_count;
		unsigned int i;

		for (i = 0; i < count; i++) {
			const struct drm_i915_gem_exec_object2 *entry =
				&eb->exec[i];
			struct drm_i915_gem_relocation_entry *relocs;

			if (!entry->relocation_count)
				continue;

			relocs = u64_to_ptr(typeof(*relocs), entry->relocs_ptr);
			kvfree(relocs);
		}
	}

	return err;
}
