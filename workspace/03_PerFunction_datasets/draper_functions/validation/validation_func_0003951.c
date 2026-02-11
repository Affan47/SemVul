AllocatePerIsolateThreadData(
    ThreadId thread_id) {
  ASSERT(!thread_id.Equals(ThreadId::Invalid()));
  PerIsolateThreadData* per_thread = new PerIsolateThreadData(this, thread_id);
  {
    ScopedLock lock(process_wide_mutex_);
    ASSERT(thread_data_table_->Lookup(this, thread_id) == NULL);
    thread_data_table_->Insert(per_thread);
    ASSERT(thread_data_table_->Lookup(this, thread_id) == per_thread);
  }
  return per_thread;
}
