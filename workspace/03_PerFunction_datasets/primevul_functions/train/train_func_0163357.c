static ssize_t copy_event_to_user(struct fsnotify_group *group,
				  struct fsnotify_event *fsn_event,
				  char __user *buf)
{
	struct inotify_event inotify_event;
	struct inotify_event_info *event;
	size_t event_size = sizeof(struct inotify_event);
	size_t name_len;
	size_t pad_name_len;

	pr_debug("%s: group=%p event=%p\n", __func__, group, fsn_event);

	event = INOTIFY_E(fsn_event);
	name_len = event->name_len;


	pad_name_len = round_event_name_len(fsn_event);
	inotify_event.len = pad_name_len;
	inotify_event.mask = inotify_mask_to_arg(event->mask);
	inotify_event.wd = event->wd;
	inotify_event.cookie = event->sync_cookie;


	if (copy_to_user(buf, &inotify_event, event_size))
		return -EFAULT;

	buf += event_size;


	if (pad_name_len) {

		if (copy_to_user(buf, event->name, name_len))
			return -EFAULT;
		buf += name_len;


		if (clear_user(buf, pad_name_len - name_len))
			return -EFAULT;
		event_size += pad_name_len;
	}

	return event_size;
}
