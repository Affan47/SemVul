AutoDetectProxy()
{


   AutoDetectProxyCmd = _config->Find("Acquire::http::Proxy-Auto-Detect",
                                      _config->Find("Acquire::http::ProxyAutoDetect"));

   if (AutoDetectProxyCmd.empty())
      return true;

   if (Debug)
      clog << "Using auto proxy detect command: " << AutoDetectProxyCmd << endl;

   int Pipes[2] = {-1,-1};
   if (pipe(Pipes) != 0)
      return _error->Errno("pipe", "Failed to create Pipe");

   pid_t Process = ExecFork();
   if (Process == 0)
   {
      close(Pipes[0]);
      dup2(Pipes[1],STDOUT_FILENO);
      SetCloseExec(STDOUT_FILENO,false);

      const char *Args[2];
      Args[0] = AutoDetectProxyCmd.c_str();
      Args[1] = 0;
      execv(Args[0],(char **)Args);
      cerr << "Failed to exec method " << Args[0] << endl;
      _exit(100);
   }
   char buf[512];
   int InFd = Pipes[0];
   close(Pipes[1]);
   int res = read(InFd, buf, sizeof(buf)-1);
   ExecWait(Process, "ProxyAutoDetect", true);

   if (res < 0)
      return _error->Errno("read", "Failed to read");
   if (res == 0)
      return _error->Warning("ProxyAutoDetect returned no data");


   buf[res] = 0;

   if (Debug)
      clog << "auto detect command returned: '" << buf << "'" << endl;

   if (strstr(buf, "http://") == buf)
      _config->Set("Acquire::http::proxy", _strstrip(buf));

   return true;
}
