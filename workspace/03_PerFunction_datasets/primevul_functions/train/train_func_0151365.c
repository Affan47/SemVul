static int futex_unlock_pi(u32 __user *uaddr, unsigned int flags)
{
	u32 uninitialized_var(curval), uval, vpid = task_pid_vnr(current);
	union futex_key key = FUTEX_KEY_INIT;
	struct futex_hash_bucket *hb;
	struct futex_q *match;
	int ret;

retry:
	if (get_user(uval, uaddr))
		return -EFAULT;


	if ((uval & FUTEX_TID_MASK) != vpid)
		return -EPERM;

	ret = get_futex_key(uaddr, flags & FLAGS_SHARED, &key, VERIFY_WRITE);
	if (ret)
		return ret;

	hb = hash_futex(&key);
	spin_lock(&hb->lock);


	match = futex_top_waiter(hb, &key);
	if (match) {
		ret = wake_futex_pi(uaddr, uval, match, hb);


		if (!ret)
			goto out_putkey;


		if (ret == -EFAULT)
			goto pi_faulted;


		goto out_unlock;
	}


	if (cmpxchg_futex_value_locked(&curval, uaddr, uval, 0))
		goto pi_faulted;


	ret = (curval == uval) ? 0 : -EAGAIN;

out_unlock:
	spin_unlock(&hb->lock);
out_putkey:
	put_futex_key(&key);
	return ret;

pi_faulted:
	spin_unlock(&hb->lock);
	put_futex_key(&key);

	ret = fault_in_user_writeable(uaddr);
	if (!ret)
		goto retry;

	return ret;
}
