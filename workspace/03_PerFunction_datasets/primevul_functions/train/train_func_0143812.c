static int rds_cancel_sent_to(struct rds_sock *rs, char __user *optval,
			      int len)
{
	struct sockaddr_in sin;
	int ret = 0;


	if (rs->rs_bound_addr == 0) {
		ret = -ENOTCONN;
		goto out;
	}

	if (len < sizeof(struct sockaddr_in)) {
		ret = -EINVAL;
		goto out;
	}

	if (copy_from_user(&sin, optval, sizeof(sin))) {
		ret = -EFAULT;
		goto out;
	}

	rds_send_drop_to(rs, &sin);
out:
	return ret;
}
