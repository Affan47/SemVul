RunProgramRemotelyWithTimeout(const sys::Path &RemoteClientPath,
                                         const char **Args,
                                         const sys::Path &StdInFile,
                                         const sys::Path &StdOutFile,
                                         const sys::Path &StdErrFile,
                                         unsigned NumSeconds = 0,
                                         unsigned MemoryLimit = 0) {
  const sys::Path* redirects[3];
  redirects[0] = &StdInFile;
  redirects[1] = &StdOutFile;
  redirects[2] = &StdErrFile;

#if 0
  {
    errs() << "RUN:";
    for (unsigned i = 0; Args[i]; ++i)
      errs() << " " << Args[i];
    errs() << "\n";
  }
#endif


  int ReturnCode = sys::Program::ExecuteAndWait(RemoteClientPath, Args,
                                 0, redirects, NumSeconds, MemoryLimit);


  if (255 == ReturnCode) {
    std::ostringstream OS;
    OS << "\nError running remote client:\n ";
    for (const char **Arg = Args; *Arg; ++Arg)
      OS << " " << *Arg;
    OS << "\n";


    std::ifstream ErrorFile(StdOutFile.c_str());
    if (ErrorFile) {
      std::copy(std::istreambuf_iterator<char>(ErrorFile),
                std::istreambuf_iterator<char>(),
                std::ostreambuf_iterator<char>(OS));
      ErrorFile.close();
    }

    errs() << OS;
  }

  return ReturnCode;
}
