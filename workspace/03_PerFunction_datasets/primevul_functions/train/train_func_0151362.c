static int futex_lock_pi_atomic(u32 __user *uaddr, struct futex_hash_bucket *hb,
				union futex_key *key,
				struct futex_pi_state **ps,
				struct task_struct *task, int set_waiters)
{
	u32 uval, newval, vpid = task_pid_vnr(task);
	struct futex_q *match;
	int ret;


	if (get_futex_value_locked(&uval, uaddr))
		return -EFAULT;

	if (unlikely(should_fail_futex(true)))
		return -EFAULT;


	if ((unlikely((uval & FUTEX_TID_MASK) == vpid)))
		return -EDEADLK;

	if ((unlikely(should_fail_futex(true))))
		return -EDEADLK;


	match = futex_top_waiter(hb, key);
	if (match)
		return attach_to_pi_state(uval, match->pi_state, ps);


	if (!(uval & FUTEX_TID_MASK)) {


		newval = uval & FUTEX_OWNER_DIED;
		newval |= vpid;


		if (set_waiters)
			newval |= FUTEX_WAITERS;

		ret = lock_pi_update_atomic(uaddr, uval, newval);

		return ret < 0 ? ret : 1;
	}


	newval = uval | FUTEX_WAITERS;
	ret = lock_pi_update_atomic(uaddr, uval, newval);
	if (ret)
		return ret;


	return attach_to_pi_owner(uval, key, ps);
}
