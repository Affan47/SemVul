ijs_server_proc_get_param (IjsServerCtx *ctx)
{
  const char *key;
  int key_size;
  int code;
  char buf[4096];
  IjsJobId job_id;

  code = ijs_recv_int (&ctx->recv_chan, &job_id);
  if (code < 0)
    return code;

  if (!ctx->in_job || ctx->job_id != job_id)
    return ijs_server_nak (ctx, IJS_EJOBID);

  key = ctx->recv_chan.buf + ctx->recv_chan.buf_idx;
  key_size = ctx->recv_chan.buf_size - ctx->recv_chan.buf_idx;
  if (key_size == 0 || key[key_size - 1])
    return IJS_ESYNTAX;
#ifdef VERBOSE
  fprintf (stderr, "ijs_server_proc_get_param, key_size = %d\n", key_size);
#endif

  code = ijs_server_get_param (ctx, job_id, key, buf, sizeof(buf));
  if (code < 0)
    return ijs_server_nak (ctx, code);
  else
    {
      int status;

      status = ijs_send_begin (&ctx->send_chan, IJS_CMD_ACK);
      if (status < 0)
	return status;
      status = ijs_send_block (&ctx->send_chan, buf, code);
      if (status < 0)
	return status;
      return ijs_send_buf (&ctx->send_chan);
    }
}
