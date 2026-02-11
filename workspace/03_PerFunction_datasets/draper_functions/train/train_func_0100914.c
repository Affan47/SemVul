BindSocket(int socketdescriptor, int port)
{
#ifndef VTK_SOCKET_FAKE_API
  struct sockaddr_in server;

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);

  int opt=1;
  int iErr=~vtkSocketErrorReturnMacro;
#ifdef _WIN32
  vtkRestartInterruptedSystemCallMacro(
    setsockopt(socketdescriptor,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(int)),
    iErr);
#elif defined(VTK_HAVE_SO_REUSEADDR)
  vtkRestartInterruptedSystemCallMacro(
    setsockopt(socketdescriptor,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(int)),
    iErr);
#endif
  if (iErr == vtkSocketErrorReturnMacro)
    {
    vtkSocketErrorMacro(vtkErrnoMacro, "Socket error in call to setsockopt.");
    return -1;
    }

  vtkRestartInterruptedSystemCallMacro(
    bind(socketdescriptor,reinterpret_cast<sockaddr*>(&server),sizeof(server)),
    iErr);
  if (iErr == vtkSocketErrorReturnMacro)
    {
    vtkSocketErrorMacro(vtkErrnoMacro, "Socket error in call to bind.");
    return -1;
    }

  return 0;
#else
  static_cast<void>(socketdescriptor);
  static_cast<void>(port);
  return -1;
#endif
}
