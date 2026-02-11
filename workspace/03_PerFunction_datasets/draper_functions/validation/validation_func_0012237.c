accounting_add_bytes(size_t n_read, size_t n_written, int seconds)
{
  n_bytes_read_in_interval += n_read;
  n_bytes_written_in_interval += n_written;


  n_seconds_active_in_interval += (seconds < 10) ? seconds : 0;
}
