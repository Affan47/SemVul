auth_heimdal_gssapi_client(
  auth_instance *ablock,
  void * sx,
  int timeout,
  uschar *buffer,
  int buffsize)
{
  HDEBUG(D_auth)
    debug_printf("Client side NOT IMPLEMENTED: you should not see this!\n");

  return FAIL;
}
