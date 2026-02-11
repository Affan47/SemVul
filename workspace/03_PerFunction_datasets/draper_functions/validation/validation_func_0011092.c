next_files_sync_check (GDaemonFileEnumerator *enumerator)
{
  g_mutex_lock (&enumerator->next_files_mutex);
  if ((enumerator->infos || enumerator->done) &&
      enumerator->next_files_mainloop != NULL)
    {
      g_main_loop_quit (enumerator->next_files_mainloop);
    }
  g_mutex_unlock (&enumerator->next_files_mutex);
}
