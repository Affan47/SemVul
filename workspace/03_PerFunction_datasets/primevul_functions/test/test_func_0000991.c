nbd_internal_command_common (struct nbd_handle *h,
                             uint16_t flags, uint16_t type,
                             uint64_t offset, uint64_t count, int count_err,
                             void *data, struct command_cb *cb)
{
  struct command *cmd;

  if (h->disconnect_request) {
      set_error (EINVAL, "cannot request more commands after NBD_CMD_DISC");
      goto err;
  }
  if (h->in_flight == INT_MAX) {
      set_error (ENOMEM, "too many commands already in flight");
      goto err;
  }

  if (count_err) {
    if ((h->strict & LIBNBD_STRICT_ZERO_SIZE) && count == 0) {
      set_error (EINVAL, "count cannot be 0");
      goto err;
    }

    if ((h->strict & LIBNBD_STRICT_BOUNDS) &&
        (offset > h->exportsize || count > h->exportsize - offset)) {
      set_error (count_err, "request out of bounds");
      goto err;
    }

    if (h->block_minimum && (h->strict & LIBNBD_STRICT_ALIGN) &&
        (offset | count) & (h->block_minimum - 1)) {
      set_error (EINVAL, "request is unaligned");
      goto err;
    }
  }

  switch (type) {

  case NBD_CMD_READ:
  case NBD_CMD_WRITE:
    if (count > MAX_REQUEST_SIZE) {
      set_error (ERANGE, "request too large: maximum request size is %d",
                 MAX_REQUEST_SIZE);
      goto err;
    }
    break;


  default:
    if (count > UINT32_MAX) {
      set_error (ERANGE, "request too large: maximum request size is %" PRIu32,
                 UINT32_MAX);
      goto err;
    }
    break;
  }

  cmd = calloc (1, sizeof *cmd);
  if (cmd == NULL) {
    set_error (errno, "calloc");
    goto err;
  }
  cmd->flags = flags;
  cmd->type = type;
  cmd->cookie = h->unique++;
  cmd->offset = offset;
  cmd->count = count;
  cmd->data = data;
  if (cb)
    cmd->cb = *cb;


  if (h->structured_replies && cmd->data && type == NBD_CMD_READ)
    memset (cmd->data, 0, cmd->count);


  h->in_flight++;
  if (h->cmds_to_issue != NULL) {
    assert (nbd_internal_is_state_processing (get_next_state (h)));
    h->cmds_to_issue_tail = h->cmds_to_issue_tail->next = cmd;
  }
  else {
    assert (h->cmds_to_issue_tail == NULL);
    h->cmds_to_issue = h->cmds_to_issue_tail = cmd;
    if (nbd_internal_is_state_ready (get_next_state (h)) &&
        nbd_internal_run (h, cmd_issue) == -1)
      debug (h, "command queued, ignoring state machine failure");
  }

  return cmd->cookie;

 err:

  if (cb) {
    if (type == NBD_CMD_BLOCK_STATUS)
      FREE_CALLBACK (cb->fn.extent);
    if (type == NBD_CMD_READ)
      FREE_CALLBACK (cb->fn.chunk);
    FREE_CALLBACK (cb->completion);
  }
  return -1;
}
