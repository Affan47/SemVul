close_listener(struct Listener *listener)
{
  assert(listener != NULL);

  if (listener == NULL)
    return;

  if (listener->fd.flags.open)
    fd_close(&listener->fd);

  listener->active = 0;

  if (listener->ref_count)
    return;

  free_listener(listener);
}
