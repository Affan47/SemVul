long keyctl_session_to_parent(void)
{
	struct task_struct *me, *parent;
	const struct cred *mycred, *pcred;
	struct callback_head *newwork, *oldwork;
	key_ref_t keyring_r;
	struct cred *cred;
	int ret;

	keyring_r = lookup_user_key(KEY_SPEC_SESSION_KEYRING, 0, KEY_LINK);
	if (IS_ERR(keyring_r))
		return PTR_ERR(keyring_r);

	ret = -ENOMEM;


	cred = cred_alloc_blank();
	if (!cred)
		goto error_keyring;
	newwork = &cred->rcu;

	cred->session_keyring = key_ref_to_ptr(keyring_r);
	keyring_r = NULL;
	init_task_work(newwork, key_change_session_keyring);

	me = current;
	rcu_read_lock();
	write_lock_irq(&tasklist_lock);

	ret = -EPERM;
	oldwork = NULL;
	parent = me->real_parent;

	task_lock(parent);

	if (parent->pid <= 1 || !parent->mm)
		goto unlock;


	if (!thread_group_empty(parent))
		goto unlock;


	mycred = current_cred();
	pcred = __task_cred(parent);
	if (mycred == pcred ||
	    mycred->session_keyring == pcred->session_keyring) {
		ret = 0;
		goto unlock;
	}


	if (pcred->uid	!= mycred->euid	||
	    pcred->euid	!= mycred->euid	||
	    pcred->suid	!= mycred->euid	||
	    pcred->gid	!= mycred->egid	||
	    pcred->egid	!= mycred->egid	||
	    pcred->sgid	!= mycred->egid)
		goto unlock;


	if ((pcred->session_keyring &&
	     pcred->session_keyring->uid != mycred->euid) ||
	    mycred->session_keyring->uid != mycred->euid)
		goto unlock;


	oldwork = task_work_cancel(parent, key_change_session_keyring);


	ret = task_work_add(parent, newwork, true);
	if (!ret)
		newwork = NULL;
unlock:
	task_unlock(parent);
	write_unlock_irq(&tasklist_lock);
	rcu_read_unlock();
	if (oldwork)
		put_cred(container_of(oldwork, struct cred, rcu));
	if (newwork)
		put_cred(cred);
	return ret;

error_keyring:
	key_ref_put(keyring_r);
	return ret;
}
