thread_data_remove_jobs_func (G_GNUC_UNUSED GThread *key, ThreadData *td, G_GNUC_UNUSED gpointer data)
{
	if (td->jobs)  {
		GSList *list;
		for (list = td->jobs; list; list = list->next) {
			Job *job = JOB (list->data);
			if (job->processed) {


				if (job->arg_destroy_func) {
					g_warning ("The argument of Job ID %d will be destroyed by sub thread",
						   job->job_id);
				}
			}
			else {

				job->cancelled = TRUE;
				if (job->arg && job->arg_destroy_func) {
					job->arg_destroy_func (job->arg);
					job->arg = NULL;
				}
			}
		}
		g_slist_free (td->jobs);
		td->jobs = NULL;
	}
	return TRUE;
}
