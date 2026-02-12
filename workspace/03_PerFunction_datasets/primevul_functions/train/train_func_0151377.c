static int attach_to_pi_state(u32 uval, struct futex_pi_state *pi_state,
			      struct futex_pi_state **ps)
{
	pid_t pid = uval & FUTEX_TID_MASK;


	if (unlikely(!pi_state))
		return -EINVAL;

	WARN_ON(!atomic_read(&pi_state->refcount));


	if (uval & FUTEX_OWNER_DIED) {


		if (!pi_state->owner) {


			if (pid)
				return -EINVAL;


			goto out_state;
		}


		if (!pid)
			goto out_state;
	} else {


		if (!pi_state->owner)
			return -EINVAL;
	}


	if (pid != task_pid_vnr(pi_state->owner))
		return -EINVAL;
out_state:
	atomic_inc(&pi_state->refcount);
	*ps = pi_state;
	return 0;
}
