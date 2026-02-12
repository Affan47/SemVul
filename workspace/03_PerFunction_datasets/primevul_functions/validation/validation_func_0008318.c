int release_threadpool(blosc2_context *context) {
  int32_t t;
  void* status;
  int rc;

  if (context->threads_started > 0) {
    if (threads_callback) {

      for (t=0; t<context->threads_started; t++)
        destroy_thread_context(context->thread_contexts + t);
      my_free(context->thread_contexts);
    }
    else {

      context->end_threads = 1;
      WAIT_INIT(-1, context);


      for (t = 0; t < context->threads_started; t++) {
        rc = pthread_join(context->threads[t], &status);
        if (rc) {
          fprintf(stderr, "ERROR; return code from pthread_join() is %d\n", rc);
          fprintf(stderr, "\tError detail: %s\n", strerror(rc));
        }
      }


      #if !defined(_WIN32)
        pthread_attr_destroy(&context->ct_attr);
      #endif


      my_free(context->threads);
    }


    pthread_mutex_destroy(&context->count_mutex);
    pthread_mutex_destroy(&context->delta_mutex);
    pthread_cond_destroy(&context->delta_cv);


  #ifdef BLOSC_POSIX_BARRIERS
    pthread_barrier_destroy(&context->barr_init);
    pthread_barrier_destroy(&context->barr_finish);
  #else
    pthread_mutex_destroy(&context->count_threads_mutex);
    pthread_cond_destroy(&context->count_threads_cv);
    context->count_threads = 0;
  #endif


    context->end_threads = 0;
    context->threads_started = 0;
  }


  return 0;
}
