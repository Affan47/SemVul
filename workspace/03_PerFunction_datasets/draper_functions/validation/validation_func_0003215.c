kmemleak_seq_start(struct seq_file *seq, loff_t *pos)
{
	struct kmemleak_object *object;
	loff_t n = *pos;
	int err;

	err = mutex_lock_interruptible(&scan_mutex);
	if (err < 0)
		return ERR_PTR(err);

	rcu_read_lock();
	list_for_each_entry_rcu(object, &object_list, object_list) {
		if (n-- > 0)
			continue;
		if (get_object(object))
			goto out;
	}
	object = NULL;
out:
	return object;
}
