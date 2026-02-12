void DU_logSelectResult(int selectReturnValue)
{
  if (selectReturnValue < 0)
  {
#ifdef HAVE_WINSOCK_H
    LPVOID errBuf = NULL;
    OFString err;

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), OFreinterpret_cast(LPTSTR, &errBuf), 0, NULL) > 0)
    {
      err = (OFstatic_cast(const char *, errBuf));
    } else
      err = "Unknown Winsock error code";
    LocalFree(errBuf);
    DCMNET_DEBUG("Windows Socket error while waiting for incoming network data: " << err);
#else

    char buf[256];
    DCMNET_DEBUG("Error while waiting for incoming network data: " << OFStandard::strerror(errno, buf, 256));
#endif
  }
  else if (selectReturnValue == 0)
  {
    DCMNET_TRACE("Timeout while waiting for incoming network data");
  }
  else
  {


    DCMNET_TRACE("Receiving data via select()");
  }
}
