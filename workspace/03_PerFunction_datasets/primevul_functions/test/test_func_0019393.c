static curlioerr my_ioctl(CURL *handle, curliocmd cmd, void *userp)
{
  struct InStruct *in=(struct InStruct *)userp;
  (void)handle;

  switch(cmd) {
  case CURLIOCMD_RESTARTREAD:

    if(-1 == fseek(in->stream, 0, SEEK_SET))


      return CURLIOE_FAILRESTART;

    break;

  default:
    return CURLIOE_UNKNOWNCMD;
  }
  return CURLIOE_OK;
}
