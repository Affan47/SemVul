reset_events_waits_current(void)
{
  PFS_thread *pfs_thread= thread_array;
  PFS_thread *pfs_thread_last= thread_array + thread_max;

  for ( ; pfs_thread < pfs_thread_last; pfs_thread++)
  {
    PFS_wait_locker *locker= pfs_thread->m_wait_locker_stack;
    PFS_wait_locker *locker_last= locker + LOCKER_STACK_SIZE;

    for ( ; locker < locker_last; locker++)
      locker->m_waits_current.m_wait_class= NO_WAIT_CLASS;
  }
}
