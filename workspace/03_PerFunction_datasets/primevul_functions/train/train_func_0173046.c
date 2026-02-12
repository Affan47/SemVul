int my_shell(char *cmd, char *result, int size) {
#ifdef OS_WINNT

                                                                                                                           HANDLE hChildStdinRd, hChildStdinWr, hChildStdinWrDup,
       hChildStdoutRd, hChildStdoutWr, hChildStderrRd, hChildStderrWr, hSaveStdin, hSaveStdout, hSaveStderr;

   SECURITY_ATTRIBUTES saAttr;
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
   char buffer[10000];
   DWORD dwRead, dwAvail, i;


   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
   saAttr.bInheritHandle = TRUE;
   saAttr.lpSecurityDescriptor = NULL;


   hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);


   if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
      return 0;


   if (!SetStdHandle(STD_OUTPUT_HANDLE, hChildStdoutWr))
      return 0;


   hSaveStderr = GetStdHandle(STD_ERROR_HANDLE);


   if (!CreatePipe(&hChildStderrRd, &hChildStderrWr, &saAttr, 0))
      return 0;


   if (!SetStdHandle(STD_ERROR_HANDLE, hChildStderrWr))
      return 0;


   hSaveStdin = GetStdHandle(STD_INPUT_HANDLE);


   if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0))
      return 0;


   if (!SetStdHandle(STD_INPUT_HANDLE, hChildStdinRd))
      return 0;


   if (!DuplicateHandle(GetCurrentProcess(), hChildStdinWr, GetCurrentProcess(), &hChildStdinWrDup, 0, FALSE,
                        DUPLICATE_SAME_ACCESS))
      return 0;

   CloseHandle(hChildStdinWr);


   memset(&siStartInfo, 0, sizeof(siStartInfo));
   siStartInfo.cb = sizeof(STARTUPINFO);
   siStartInfo.lpReserved = NULL;
   siStartInfo.lpReserved2 = NULL;
   siStartInfo.cbReserved2 = 0;
   siStartInfo.lpDesktop = NULL;
   siStartInfo.dwFlags = 0;


   sprintf(buffer, "cmd /q /c %s", cmd);

   if (!CreateProcess(NULL, buffer,
                      NULL,
                      NULL,
                      TRUE,
                      0,
                      NULL,
                      NULL,
                      &siStartInfo,
                      &piProcInfo))
      return 0;


   SetStdHandle(STD_INPUT_HANDLE, hSaveStdin);
   SetStdHandle(STD_OUTPUT_HANDLE, hSaveStdout);
   SetStdHandle(STD_ERROR_HANDLE, hSaveStderr);

   memset(result, 0, size);

   do {

      do {
         if (!PeekNamedPipe(hChildStdoutRd, buffer, 256, &dwRead, &dwAvail, NULL))
            break;
         if (dwRead > 0) {
            ReadFile(hChildStdoutRd, buffer, 256, &dwRead, NULL);
            buffer[dwRead] = 0;
            strlcat(result, buffer, size);
         }
      } while (dwAvail > 0);


      do {
         if (!PeekNamedPipe(hChildStderrRd, buffer, 256, &dwRead, &dwAvail, NULL))
            break;
         if (dwRead > 0) {
            ReadFile(hChildStderrRd, buffer, 256, &dwRead, NULL);
            buffer[dwRead] = 0;
            strlcat(result, buffer, size);
         }
      } while (dwAvail > 0);


      if (!GetExitCodeProcess(piProcInfo.hProcess, &i))
         break;
      if (i != STILL_ACTIVE)
         break;


      Sleep(10);

   } while (TRUE);

   CloseHandle(hChildStdinWrDup);
   CloseHandle(hChildStdinRd);
   CloseHandle(hChildStderrRd);
   CloseHandle(hChildStdoutRd);


   while (strlen(result) > 0 && (result[strlen(result) - 1] == '\r' || result[strlen(result) - 1] == '\n'))
      result[strlen(result) - 1] = 0;

   return 1;

#endif

#ifdef OS_UNIX
   pid_t child_pid;
   int fh, status, wait_status;
   char str[1024];
   char tmp_filename[1024];

   strlcpy(tmp_filename, "/tmp/elog_XXXXXX", sizeof(tmp_filename));
   fh = mkstemp(tmp_filename);
   if (fh == 0) {
      eprintf("Error getting TMP file name.\n");
      return 0;
   }
   close(fh);

   if ((child_pid = fork()) < 0)
      return 0;
   else if (child_pid > 0) {

      do {
         wait_status = waitpid(child_pid, &status, 0);
      } while (wait_status == -1 && errno == EINTR);


      memset(result, 0, size);
      fh = open(tmp_filename, O_RDONLY);
      if (fh > 0) {
         read(fh, result, size - 1);
         close(fh);
      }


      remove(tmp_filename);


      while (strlen(result) > 0 && (result[strlen(result) - 1] == '\r' || result[strlen(result) - 1] == '\n'))
         result[strlen(result) - 1] = 0;

   } else {


      if (setregid(-1, orig_gid) < 0 || setreuid(-1, orig_uid) < 0)
         eprintf("Cannot restore original GID/UID.\n");


      if (geteuid() == 0) {
         if (!getcfg("global", "Grp", str, sizeof(str)) || setgroup(str) < 0) {
            eprintf("Falling back to default group \"elog\"\n");
            if (setgroup("elog") < 0) {
               eprintf("Falling back to default group \"%s\"\n", DEFAULT_GROUP);
               if (setgroup(DEFAULT_GROUP) < 0) {
                  eprintf("Refuse to run as setgid root.\n");
                  eprintf("Please consider to define a Grp statement in configuration file\n");
                  exit(EXIT_FAILURE);
               }
            }
         } else if (get_verbose() >= VERBOSE_INFO)
            eprintf("Falling back to group \"%s\"\n", str);

         if (!getcfg("global", "Usr", str, sizeof(str)) || setuser(str) < 0) {
            eprintf("Falling back to default user \"elog\"\n");
            if (setuser("elog") < 0) {
               eprintf("Falling back to default user \"%s\"\n", DEFAULT_USER);
               if (setuser(DEFAULT_USER) < 0) {
                  eprintf("Refuse to run as setuid root.\n");
                  eprintf("Please consider to define a Usr statement in configuration file\n");
                  exit(EXIT_FAILURE);
               }
            }
         } else if (get_verbose() >= VERBOSE_INFO)
            eprintf("Falling back to user \"%s\"\n", str);
      }


      sprintf(str, "/bin/sh -c \"%s\" > %s 2>&1", cmd, tmp_filename);

      if (get_verbose() >= VERBOSE_INFO) {
         efputs("Going to execute: ");
         efputs(str);
         efputs("\n");
      }

      system(str);
      _exit(0);
   }

   return 1;

#endif
}
