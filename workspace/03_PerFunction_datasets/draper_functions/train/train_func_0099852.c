lam_setfunc(int locfunc)
{


  if (stack == NULL)
    if (lam_updown_init() == LAMERROR)
      return;

#if LAM_HAVE_THREADS


  if (lam_mpi_thread_level == MPI_THREAD_SERIALIZED) {
    if (!lam_mutex_is_owner(&lam_mpi_mutex)) {
      lam_mutex_lock(&lam_mpi_mutex);
    }
  }

#endif


  ++stack_size;
  lam_arr_append(stack, &locfunc);
  func_stack = lam_arr_get(stack);
  if (stack_size == 1)
    ((struct _fyiproc *) _kio.ki_fyi)->fyp_func = locfunc;
  lam_topfunc = locfunc;
}
