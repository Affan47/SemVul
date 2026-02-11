flush_log_output (void)
{
  if (log_file)
    fflush (log_file);
}
