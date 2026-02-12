void decoder_context::stop_thread_pool()
{
  if (get_num_worker_threads()>0) {

    ::stop_thread_pool(&thread_pool_);
  }
}
