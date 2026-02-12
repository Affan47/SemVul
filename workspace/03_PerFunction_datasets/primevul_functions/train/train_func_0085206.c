do_start_bgworker(RegisteredBgWorker *rw)
{
	pid_t		worker_pid;

	Assert(rw->rw_pid == 0);


	if (!assign_backendlist_entry(rw))
	{
		rw->rw_crashed_at = GetCurrentTimestamp();
		return false;
	}

	ereport(DEBUG1,
			(errmsg_internal("starting background worker process \"%s\"",
							 rw->rw_worker.bgw_name)));

#ifdef EXEC_BACKEND
	switch ((worker_pid = bgworker_forkexec(rw->rw_shmem_slot)))
#else
	switch ((worker_pid = fork_process()))
#endif
	{
		case -1:

			ereport(LOG,
					(errmsg("could not fork worker process: %m")));

			ReleasePostmasterChildSlot(rw->rw_child_slot);
			rw->rw_child_slot = 0;
			free(rw->rw_backend);
			rw->rw_backend = NULL;

			rw->rw_crashed_at = GetCurrentTimestamp();
			break;

#ifndef EXEC_BACKEND
		case 0:

			InitPostmasterChild();


			ClosePostmasterPorts(false);


			MyBgworkerEntry = (BackgroundWorker *)
				MemoryContextAlloc(TopMemoryContext, sizeof(BackgroundWorker));
			memcpy(MyBgworkerEntry, &rw->rw_worker, sizeof(BackgroundWorker));


			MemoryContextSwitchTo(TopMemoryContext);
			MemoryContextDelete(PostmasterContext);
			PostmasterContext = NULL;

			StartBackgroundWorker();

			exit(1);
			break;
#endif
		default:

			rw->rw_pid = worker_pid;
			rw->rw_backend->pid = rw->rw_pid;
			ReportBackgroundWorkerPID(rw);

			dlist_push_head(&BackendList, &rw->rw_backend->elem);
#ifdef EXEC_BACKEND
			ShmemBackendArrayAdd(rw->rw_backend);
#endif
			return true;
	}

	return false;
}
