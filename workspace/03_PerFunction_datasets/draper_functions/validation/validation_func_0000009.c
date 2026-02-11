set_worker_thread_count(sge_bootstrap_state_class_t *thiz, int thread_count)
{
   sge_bootstrap_state_t *es = (sge_bootstrap_state_t *) thiz->sge_bootstrap_state_handle;

   if (thread_count <= 0) {
      thread_count = 2;
   } else if (thread_count > 16) {
      thread_count = 16;
   }
   es->worker_thread_count = thread_count;
}
