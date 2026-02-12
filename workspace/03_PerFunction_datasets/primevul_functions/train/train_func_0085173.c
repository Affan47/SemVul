CleanupBackgroundWorker(int pid,
						int exitstatus)
{
	char		namebuf[MAXPGPATH];
	slist_mutable_iter iter;

	slist_foreach_modify(iter, &BackgroundWorkerList)
	{
		RegisteredBgWorker *rw;

		rw = slist_container(RegisteredBgWorker, rw_lnode, iter.cur);

		if (rw->rw_pid != pid)
			continue;

#ifdef WIN32

		if (exitstatus == ERROR_WAIT_NO_CHILDREN)
			exitstatus = 0;
#endif

		snprintf(namebuf, MAXPGPATH, _("background worker \"%s\""),
				 rw->rw_worker.bgw_type);


		if (!EXIT_STATUS_0(exitstatus))
		{

			rw->rw_crashed_at = GetCurrentTimestamp();
		}
		else
		{

			rw->rw_crashed_at = 0;
			rw->rw_terminate = true;
		}


		if (!EXIT_STATUS_0(exitstatus) && !EXIT_STATUS_1(exitstatus))
		{
			HandleChildCrash(pid, exitstatus, namebuf);
			return true;
		}


		if (!ReleasePostmasterChildSlot(rw->rw_child_slot))
		{
			HandleChildCrash(pid, exitstatus, namebuf);
			return true;
		}


		dlist_delete(&rw->rw_backend->elem);
#ifdef EXEC_BACKEND
		ShmemBackendArrayRemove(rw->rw_backend);
#endif


		if (rw->rw_backend->bgworker_notify)
			BackgroundWorkerStopNotifications(rw->rw_pid);
		free(rw->rw_backend);
		rw->rw_backend = NULL;
		rw->rw_pid = 0;
		rw->rw_child_slot = 0;
		ReportBackgroundWorkerExit(&iter);

		LogChildExit(EXIT_STATUS_0(exitstatus) ? DEBUG1 : LOG,
					 namebuf, pid, exitstatus);

		return true;
	}

	return false;
}
