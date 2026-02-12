static int do_job(blosc2_context* context) {
  int32_t ntbytes;


  context->dref_not_init = 1;


  check_nthreads(context);


  if (context->nthreads == 1 || (context->sourcesize / context->blocksize) <= 1) {

    if (context->serial_context == NULL) {
      context->serial_context = create_thread_context(context, 0);
    }
    else if (context->blocksize != context->serial_context->tmp_blocksize) {
      free_thread_context(context->serial_context);
      context->serial_context = create_thread_context(context, 0);
    }
    ntbytes = serial_blosc(context->serial_context);
  }
  else {
    ntbytes = parallel_blosc(context);
  }

  return ntbytes;
}
