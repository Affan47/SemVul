static ssize_t xenbus_file_write(struct file *filp,
				const char __user *ubuf,
				size_t len, loff_t *ppos)
{
	struct xenbus_file_priv *u = filp->private_data;
	uint32_t msg_type;
	int rc = len;
	int ret;
	LIST_HEAD(staging_q);


	mutex_lock(&u->msgbuffer_mutex);


	if (len == 0)
		goto out;


	if (len > sizeof(u->u.buffer) - u->len) {

		u->len = 0;
		rc = -EINVAL;
		goto out;
	}

	ret = copy_from_user(u->u.buffer + u->len, ubuf, len);

	if (ret != 0) {
		rc = -EFAULT;
		goto out;
	}


	len -= ret;
	rc = len;

	u->len += len;


	if (u->len < sizeof(u->u.msg))
		goto out;


	if ((sizeof(u->u.msg) + u->u.msg.len) > sizeof(u->u.buffer)) {
		rc = -E2BIG;
		u->len = 0;
		goto out;
	}

	if (u->len < (sizeof(u->u.msg) + u->u.msg.len))
		goto out;


	msg_type = u->u.msg.type;

	switch (msg_type) {
	case XS_WATCH:
	case XS_UNWATCH:

		ret = xenbus_write_watch(msg_type, u);
		break;

	default:

		ret = xenbus_write_transaction(msg_type, u);
		break;
	}
	if (ret != 0)
		rc = ret;


	u->len = 0;

 out:
	mutex_unlock(&u->msgbuffer_mutex);
	return rc;
}
