scm_async_click ()
{
  scm_i_thread *t = SCM_I_CURRENT_THREAD;
  SCM asyncs;


  scm_i_pthread_mutex_lock (&async_mutex);
  t->pending_asyncs = 0;
  if (t->block_asyncs == 0)
    {
      asyncs = t->active_asyncs;
      t->active_asyncs = SCM_EOL;
    }
  else
    asyncs = SCM_EOL;
  scm_i_pthread_mutex_unlock (&async_mutex);

  while (scm_is_pair (asyncs))
    {
      SCM next = SCM_CDR (asyncs);
      SCM_SETCDR (asyncs, SCM_BOOL_F);
      scm_call_0 (SCM_CAR (asyncs));
      asyncs = next;
    }
}
