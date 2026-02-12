static void __input_release_device(struct input_handle *handle)
{
	struct input_dev *dev = handle->dev;
	struct input_handle *grabber;

	grabber = rcu_dereference_protected(dev->grab,
					    lockdep_is_held(&dev->mutex));
	if (grabber == handle) {
		rcu_assign_pointer(dev->grab, NULL);

		synchronize_rcu();

		list_for_each_entry(handle, &dev->h_list, d_node)
			if (handle->open && handle->handler->start)
				handle->handler->start(handle);
	}
}
