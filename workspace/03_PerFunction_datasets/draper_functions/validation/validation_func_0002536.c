__w1_remove_master_device(struct w1_master *dev)
{
	struct w1_netlink_msg msg;
	struct w1_slave *sl, *sln;

	mutex_lock(&w1_mlock);
	list_del(&dev->w1_master_entry);
	mutex_unlock(&w1_mlock);

	set_bit(W1_ABORT_SEARCH, &dev->flags);
	kthread_stop(dev->thread);

	mutex_lock(&dev->mutex);
	mutex_lock(&dev->list_mutex);
	list_for_each_entry_safe(sl, sln, &dev->slist, w1_slave_entry) {
		mutex_unlock(&dev->list_mutex);
		w1_slave_detach(sl);
		mutex_lock(&dev->list_mutex);
	}
	w1_destroy_master_attributes(dev);
	mutex_unlock(&dev->list_mutex);
	mutex_unlock(&dev->mutex);
	atomic_dec(&dev->refcnt);

	while (atomic_read(&dev->refcnt)) {
		dev_info(&dev->dev, "Waiting for %s to become free: refcnt=%d.\n",
				dev->name, atomic_read(&dev->refcnt));

		if (msleep_interruptible(1000))
			flush_signals(current);
		mutex_lock(&dev->list_mutex);
		w1_process_callbacks(dev);
		mutex_unlock(&dev->list_mutex);
	}
	mutex_lock(&dev->list_mutex);
	w1_process_callbacks(dev);
	mutex_unlock(&dev->list_mutex);

	memset(&msg, 0, sizeof(msg));
	msg.id.mst.id = dev->id;
	msg.type = W1_MASTER_REMOVE;
	w1_netlink_send(dev, &msg);

	w1_free_dev(dev);
}
