set_thread_id_v1(PSI_thread *thread, unsigned long id)
{
  DBUG_ASSERT(thread);
  PFS_thread *pfs= reinterpret_cast<PFS_thread*> (thread);
  pfs->m_thread_id= id;
}
