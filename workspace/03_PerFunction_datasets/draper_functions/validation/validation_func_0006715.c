genie_lock (NODE_T * p)
{
  A68_REF ref_file;
  A68_FILE *file;
  POP_REF (p, &ref_file);
  CHECK_REF (p, ref_file, MODE (REF_FILE));
  file = FILE_DEREF (&ref_file);
  CHECK_INIT (p, INITIALISED (file), MODE (FILE));
  if (!OPENED (file) || (!READ_MOOD (file) && !WRITE_MOOD (file) && !DRAW_MOOD (file))) {
    return;
  }
  DEVICE_MADE (&DEVICE (file)) = A68_FALSE;
#if defined HAVE_GNU_PLOTUTILS
  if (DEVICE_OPENED (&DEVICE (file))) {
    ASSERT(close_device (p, file) == A68_TRUE);
    STREAM (&DEVICE (file)) = NO_STREAM;
    return;
  }
#endif
#if ! defined HAVE_WIN32
  RESET_ERRNO;
  ASSERT (fchmod (FD (file), (mode_t) 0x0) != -1);
#endif
  if (FD (file) != A68_NO_FILENO && close (FD (file)) == -1) {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_FILE_LOCK);
    exit_genie (p, A68_RUNTIME_ERROR);
  } else {
    FD (file) = A68_NO_FILENO;
    OPENED (file) = A68_FALSE;
    unblock_transput_buffer (TRANSPUT_BUFFER (file));
    set_default_event_procedures (file);
  }
  free_file_entry (p, FILE_ENTRY (file));
}
