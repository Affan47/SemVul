static int de_thread(struct task_struct *tsk)
{
	struct signal_struct *sig = tsk->signal;
	struct sighand_struct *newsighand, *oldsighand = tsk->sighand;
	spinlock_t *lock = &oldsighand->siglock;
	struct task_struct *leader = NULL;
	int count;


	signalfd_detach(tsk);


	if (atomic_read(&oldsighand->count) <= 1) {
		BUG_ON(atomic_read(&sig->count) != 1);
		exit_itimers(sig);
		return 0;
	}

	newsighand = kmem_cache_alloc(sighand_cachep, GFP_KERNEL);
	if (!newsighand)
		return -ENOMEM;

	if (thread_group_empty(tsk))
		goto no_thread_group;


	read_lock(&tasklist_lock);
	spin_lock_irq(lock);
	if (sig->flags & SIGNAL_GROUP_EXIT) {


		spin_unlock_irq(lock);
		read_unlock(&tasklist_lock);
		kmem_cache_free(sighand_cachep, newsighand);
		return -EAGAIN;
	}


	if (unlikely(tsk->group_leader == child_reaper(tsk)))
		tsk->nsproxy->pid_ns->child_reaper = tsk;

	zap_other_threads(tsk);
	read_unlock(&tasklist_lock);


	count = 1;
	if (!thread_group_leader(tsk)) {
		count = 2;


		sig->tsk = tsk;
		spin_unlock_irq(lock);
		if (hrtimer_cancel(&sig->real_timer))
			hrtimer_restart(&sig->real_timer);
		spin_lock_irq(lock);
	}
	while (atomic_read(&sig->count) > count) {
		sig->group_exit_task = tsk;
		sig->notify_count = count;
		__set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(lock);
		schedule();
		spin_lock_irq(lock);
	}
	sig->group_exit_task = NULL;
	sig->notify_count = 0;
	spin_unlock_irq(lock);


	if (!thread_group_leader(tsk)) {


		leader = tsk->group_leader;
		while (leader->exit_state != EXIT_ZOMBIE)
			yield();


		tsk->start_time = leader->start_time;

		write_lock_irq(&tasklist_lock);

		BUG_ON(leader->tgid != tsk->tgid);
		BUG_ON(tsk->pid == tsk->tgid);


		detach_pid(tsk, PIDTYPE_PID);
		tsk->pid = leader->pid;
		attach_pid(tsk, PIDTYPE_PID,  find_pid(tsk->pid));
		transfer_pid(leader, tsk, PIDTYPE_PGID);
		transfer_pid(leader, tsk, PIDTYPE_SID);
		list_replace_rcu(&leader->tasks, &tsk->tasks);

		tsk->group_leader = tsk;
		leader->group_leader = tsk;

		tsk->exit_signal = SIGCHLD;

		BUG_ON(leader->exit_state != EXIT_ZOMBIE);
		leader->exit_state = EXIT_DEAD;

		write_unlock_irq(&tasklist_lock);
        }


	sig->flags = 0;

no_thread_group:
	exit_itimers(sig);
	if (leader)
		release_task(leader);

	BUG_ON(atomic_read(&sig->count) != 1);

	if (atomic_read(&oldsighand->count) == 1) {


		kmem_cache_free(sighand_cachep, newsighand);
	} else {


		atomic_set(&newsighand->count, 1);
		memcpy(newsighand->action, oldsighand->action,
		       sizeof(newsighand->action));

		write_lock_irq(&tasklist_lock);
		spin_lock(&oldsighand->siglock);
		spin_lock_nested(&newsighand->siglock, SINGLE_DEPTH_NESTING);

		rcu_assign_pointer(tsk->sighand, newsighand);
		recalc_sigpending();

		spin_unlock(&newsighand->siglock);
		spin_unlock(&oldsighand->siglock);
		write_unlock_irq(&tasklist_lock);

		__cleanup_sighand(oldsighand);
	}

	BUG_ON(!thread_group_leader(tsk));
	return 0;
}
