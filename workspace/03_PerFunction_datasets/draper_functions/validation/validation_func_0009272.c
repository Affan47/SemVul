read_bytes(void* target_buffer, long int bytes)
{

  long int res = ::read(fd_rep, target_buffer, 1);
  if (res >= 0) return res;
  finished_rep = true;
  return 0;
}
