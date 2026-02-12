void elv_unregister_queue(struct request_queue *q)
{
	lockdep_assert_held(&q->sysfs_lock);

	if (q) {
		struct elevator_queue *e = q->elevator;

		kobject_uevent(&e->kobj, KOBJ_REMOVE);
		kobject_del(&e->kobj);
		e->registered = 0;

		wbt_enable_default(q);
	}
}
