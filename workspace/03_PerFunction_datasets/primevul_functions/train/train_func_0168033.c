NCR_DestroyInstance(NCR_Instance instance)
{
  if (instance->opmode != MD_OFFLINE)
    take_offline(instance);

  if (instance->mode == MODE_ACTIVE)
    NIO_CloseServerSocket(instance->local_addr.sock_fd);


  SRC_DestroyInstance(instance->source);


  Free(instance);
}
