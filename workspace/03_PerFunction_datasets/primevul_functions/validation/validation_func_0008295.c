static int parallel_blosc(blosc2_context* context) {
#ifdef BLOSC_POSIX_BARRIERS
  int rc;
#endif

  context->thread_giveup_code = 1;
  context->thread_nblock = -1;

  if (threads_callback) {
    threads_callback(threads_callback_data, t_blosc_do_job,
                     context->nthreads, sizeof(struct thread_context), (void*) context->thread_contexts);
  }
  else {

    WAIT_INIT(-1, context);


    WAIT_FINISH(-1, context);
  }

  if (context->thread_giveup_code <= 0) {

    return context->thread_giveup_code;
  }


  return (int)context->output_bytes;
}
