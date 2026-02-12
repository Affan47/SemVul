SYSCALL_DEFINE5(perf_event_open,
		struct perf_event_attr __user *, attr_uptr,
		pid_t, pid, int, cpu, int, group_fd, unsigned long, flags)
{
	struct perf_event *group_leader = NULL, *output_event = NULL;
	struct perf_event *event, *sibling;
	struct perf_event_attr attr;
	struct perf_event_context *ctx, *gctx;
	struct file *event_file = NULL;
	struct fd group = {NULL, 0};
	struct task_struct *task = NULL;
	struct pmu *pmu;
	int event_fd;
	int move_group = 0;
	int err;
	int f_flags = O_RDWR;
	int cgroup_fd = -1;


	if (flags & ~PERF_FLAG_ALL)
		return -EINVAL;


	err = security_perf_event_open(&attr, PERF_SECURITY_OPEN);
	if (err)
		return err;

	err = perf_copy_attr(attr_uptr, &attr);
	if (err)
		return err;

	if (!attr.exclude_kernel) {
		err = perf_allow_kernel(&attr);
		if (err)
			return err;
	}

	if (attr.namespaces) {
		if (!perfmon_capable())
			return -EACCES;
	}

	if (attr.freq) {
		if (attr.sample_freq > sysctl_perf_event_sample_rate)
			return -EINVAL;
	} else {
		if (attr.sample_period & (1ULL << 63))
			return -EINVAL;
	}


	if ((attr.sample_type & PERF_SAMPLE_PHYS_ADDR)) {
		err = perf_allow_kernel(&attr);
		if (err)
			return err;
	}

	err = security_locked_down(LOCKDOWN_PERF);
	if (err && (attr.sample_type & PERF_SAMPLE_REGS_INTR))

		return err;

	err = 0;


	if ((flags & PERF_FLAG_PID_CGROUP) && (pid == -1 || cpu == -1))
		return -EINVAL;

	if (flags & PERF_FLAG_FD_CLOEXEC)
		f_flags |= O_CLOEXEC;

	event_fd = get_unused_fd_flags(f_flags);
	if (event_fd < 0)
		return event_fd;

	if (group_fd != -1) {
		err = perf_fget_light(group_fd, &group);
		if (err)
			goto err_fd;
		group_leader = group.file->private_data;
		if (flags & PERF_FLAG_FD_OUTPUT)
			output_event = group_leader;
		if (flags & PERF_FLAG_FD_NO_GROUP)
			group_leader = NULL;
	}

	if (pid != -1 && !(flags & PERF_FLAG_PID_CGROUP)) {
		task = find_lively_task_by_vpid(pid);
		if (IS_ERR(task)) {
			err = PTR_ERR(task);
			goto err_group_fd;
		}
	}

	if (task && group_leader &&
	    group_leader->attr.inherit != attr.inherit) {
		err = -EINVAL;
		goto err_task;
	}

	if (task) {
		err = mutex_lock_interruptible(&task->signal->exec_update_mutex);
		if (err)
			goto err_task;


		err = -EACCES;
		if (!perfmon_capable() && !ptrace_may_access(task, PTRACE_MODE_READ_REALCREDS))
			goto err_cred;
	}

	if (flags & PERF_FLAG_PID_CGROUP)
		cgroup_fd = pid;

	event = perf_event_alloc(&attr, cpu, task, group_leader, NULL,
				 NULL, NULL, cgroup_fd);
	if (IS_ERR(event)) {
		err = PTR_ERR(event);
		goto err_cred;
	}

	if (is_sampling_event(event)) {
		if (event->pmu->capabilities & PERF_PMU_CAP_NO_INTERRUPT) {
			err = -EOPNOTSUPP;
			goto err_alloc;
		}
	}


	pmu = event->pmu;

	if (attr.use_clockid) {
		err = perf_event_set_clock(event, attr.clockid);
		if (err)
			goto err_alloc;
	}

	if (pmu->task_ctx_nr == perf_sw_context)
		event->event_caps |= PERF_EV_CAP_SOFTWARE;

	if (group_leader) {
		if (is_software_event(event) &&
		    !in_software_context(group_leader)) {


			pmu = group_leader->ctx->pmu;
		} else if (!is_software_event(event) &&
			   is_software_event(group_leader) &&
			   (group_leader->group_caps & PERF_EV_CAP_SOFTWARE)) {


			move_group = 1;
		}
	}


	ctx = find_get_context(pmu, task, event);
	if (IS_ERR(ctx)) {
		err = PTR_ERR(ctx);
		goto err_alloc;
	}


	if (group_leader) {
		err = -EINVAL;


		if (group_leader->group_leader != group_leader)
			goto err_context;


		if (group_leader->clock != event->clock)
			goto err_context;


		if (group_leader->cpu != event->cpu)
			goto err_context;


		if (group_leader->ctx->task != ctx->task)
			goto err_context;


		if (!move_group && group_leader->ctx != ctx)
			goto err_context;


		if (attr.exclusive || attr.pinned)
			goto err_context;
	}

	if (output_event) {
		err = perf_event_set_output(event, output_event);
		if (err)
			goto err_context;
	}

	event_file = anon_inode_getfile("[perf_event]", &perf_fops, event,
					f_flags);
	if (IS_ERR(event_file)) {
		err = PTR_ERR(event_file);
		event_file = NULL;
		goto err_context;
	}

	if (move_group) {
		gctx = __perf_event_ctx_lock_double(group_leader, ctx);

		if (gctx->task == TASK_TOMBSTONE) {
			err = -ESRCH;
			goto err_locked;
		}


		if (!(group_leader->group_caps & PERF_EV_CAP_SOFTWARE)) {


			if (gctx != ctx) {
				err = -EINVAL;
				goto err_locked;
			} else {
				perf_event_ctx_unlock(group_leader, gctx);
				move_group = 0;
			}
		}


		err = -EBUSY;
		if (!exclusive_event_installable(group_leader, ctx))
			goto err_locked;

		for_each_sibling_event(sibling, group_leader) {
			if (!exclusive_event_installable(sibling, ctx))
				goto err_locked;
		}
	} else {
		mutex_lock(&ctx->mutex);
	}

	if (ctx->task == TASK_TOMBSTONE) {
		err = -ESRCH;
		goto err_locked;
	}

	if (!perf_event_validate_size(event)) {
		err = -E2BIG;
		goto err_locked;
	}

	if (!task) {


		struct perf_cpu_context *cpuctx =
			container_of(ctx, struct perf_cpu_context, ctx);

		if (!cpuctx->online) {
			err = -ENODEV;
			goto err_locked;
		}
	}

	if (perf_need_aux_event(event) && !perf_get_aux_event(event, group_leader)) {
		err = -EINVAL;
		goto err_locked;
	}


	if (!exclusive_event_installable(event, ctx)) {
		err = -EBUSY;
		goto err_locked;
	}

	WARN_ON_ONCE(ctx->parent_ctx);


	if (move_group) {


		perf_remove_from_context(group_leader, 0);
		put_ctx(gctx);

		for_each_sibling_event(sibling, group_leader) {
			perf_remove_from_context(sibling, 0);
			put_ctx(gctx);
		}


		synchronize_rcu();


		for_each_sibling_event(sibling, group_leader) {
			perf_event__state_init(sibling);
			perf_install_in_context(ctx, sibling, sibling->cpu);
			get_ctx(ctx);
		}


		perf_event__state_init(group_leader);
		perf_install_in_context(ctx, group_leader, group_leader->cpu);
		get_ctx(ctx);
	}


	perf_event__header_size(event);
	perf_event__id_header_size(event);

	event->owner = current;

	perf_install_in_context(ctx, event, event->cpu);
	perf_unpin_context(ctx);

	if (move_group)
		perf_event_ctx_unlock(group_leader, gctx);
	mutex_unlock(&ctx->mutex);

	if (task) {
		mutex_unlock(&task->signal->exec_update_mutex);
		put_task_struct(task);
	}

	mutex_lock(&current->perf_event_mutex);
	list_add_tail(&event->owner_entry, &current->perf_event_list);
	mutex_unlock(&current->perf_event_mutex);


	fdput(group);
	fd_install(event_fd, event_file);
	return event_fd;

err_locked:
	if (move_group)
		perf_event_ctx_unlock(group_leader, gctx);
	mutex_unlock(&ctx->mutex);

	fput(event_file);
err_context:
	perf_unpin_context(ctx);
	put_ctx(ctx);
err_alloc:


	if (!event_file)
		free_event(event);
err_cred:
	if (task)
		mutex_unlock(&task->signal->exec_update_mutex);
err_task:
	if (task)
		put_task_struct(task);
err_group_fd:
	fdput(group);
err_fd:
	put_unused_fd(event_fd);
	return err;
}
