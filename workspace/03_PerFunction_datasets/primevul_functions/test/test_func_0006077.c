static GFINLINE void gf_fs_sema_io(GF_FilterSession *fsess, Bool notify, Bool main)
{
	GF_Semaphore *sem = main ? fsess->semaphore_main : fsess->semaphore_other;
	if (sem) {
		if (notify) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_SCHEDULER, ("Thread %u notify scheduler %s semaphore\n", gf_th_id(), main ? "main" : "secondary"));
			if ( ! gf_sema_notify(sem, 1)) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_SCHEDULER, ("Cannot notify scheduler of new task, semaphore failure\n"));
			}
		} else {
			u32 nb_tasks;


			if (!main && fsess->in_main_sem_wait && !gf_fq_count(fsess->main_thread_tasks)) {
				gf_fs_sema_io(fsess, GF_TRUE, GF_TRUE);
			}
			nb_tasks = 1;

			if (!fsess->active_threads)
			 	nb_tasks = gf_fq_count(fsess->main_thread_tasks) + gf_fq_count(fsess->tasks);


			if (main) {
				fsess->in_main_sem_wait = GF_TRUE;
				if (!nb_tasks) {
					GF_LOG(GF_LOG_DEBUG, GF_LOG_SCHEDULER, ("No tasks scheduled, waiting on main semaphore for at most 100 ms\n"));
					if (gf_sema_wait_for(sem, 100)) {
					}
				} else {
					if (gf_sema_wait(sem)) {
					}
				}
				fsess->in_main_sem_wait = GF_FALSE;
			} else {
				if (!nb_tasks) {
					GF_LOG(GF_LOG_DEBUG, GF_LOG_SCHEDULER, ("No tasks scheduled, waiting on secondary semaphore for at most 100 ms\n"));
					if (gf_sema_wait_for(sem, 100)) {
					}
				} else {
					if (gf_sema_wait(sem)) {
					}
				}
			}
		}
	}
}
