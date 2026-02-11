handle_read(HIME_client_handle *handle, void *ptr, int n)
{
  int fd = handle->fd;

  if (!fd)
    return 0;

  SAVE_ACT save_act;
  save_old_sigaction(&save_act);
  int r = read(fd, ptr, n);

#if (DBG || 1)
  if (r < 0)
    perror("handle_read");
#endif

  restore_old_sigaction(&save_act);

  if (r<=0)
    return r;
  if (handle->passwd)
    __hime_enc_mem((u_char *)ptr, n, handle->passwd, &handle->passwd->seed);
  return r;
}
