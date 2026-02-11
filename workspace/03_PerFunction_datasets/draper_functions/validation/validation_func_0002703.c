GC_inner_start_routine(struct GC_stack_base *sb, void *arg)
{
  void * (*start)(void *);
  void * start_arg;
  void * result;
  volatile GC_thread me =
                GC_start_rtn_prepare_thread(&start, &start_arg, sb, arg);

# ifndef NACL
    pthread_cleanup_push(GC_thread_exit_proc, me);
# endif
  result = (*start)(start_arg);
# ifdef DEBUG_THREADS
    GC_log_printf("Finishing thread 0x%x\n", (unsigned)pthread_self());
# endif
  me -> status = result;
# ifndef NACL
    pthread_cleanup_pop(1);


# endif
  return result;
}
