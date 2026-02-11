enumerate_job_finish (EnumerateJob *job)
{
  GSList *files = job->logs;
  LogviewApp *app = job->app;

  logview_manager_add_logs_from_name_list (app->priv->manager, files, files->data);

  g_slist_foreach (files, (GFunc) g_free, NULL);
  g_slist_free (files);

  g_object_unref (job->app);
  g_slice_free (EnumerateJob, job);
}
