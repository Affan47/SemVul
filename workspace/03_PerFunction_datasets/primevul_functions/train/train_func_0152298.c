_read_subprocess_line_argv (const char *progpath,
                            dbus_bool_t path_fallback,
                            const char * const *argv,
                            DBusString *result,
                            DBusError  *error)
{
  int result_pipe[2] = { -1, -1 };
  int errors_pipe[2] = { -1, -1 };
  pid_t pid;
  int ret;
  int status;
  int orig_len;

  dbus_bool_t retval;
  sigset_t new_set, old_set;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  retval = FALSE;


  sigemptyset (&new_set);
  sigaddset (&new_set, SIGCHLD);
  sigprocmask (SIG_BLOCK, &new_set, &old_set);

  orig_len = _dbus_string_get_length (result);

#define READ_END        0
#define WRITE_END       1
  if (pipe (result_pipe) < 0)
    {
      dbus_set_error (error, _dbus_error_from_errno (errno),
                      "Failed to create a pipe to call %s: %s",
                      progpath, _dbus_strerror (errno));
      _dbus_verbose ("Failed to create a pipe to call %s: %s\n",
                     progpath, _dbus_strerror (errno));
      goto out;
    }
  if (pipe (errors_pipe) < 0)
    {
      dbus_set_error (error, _dbus_error_from_errno (errno),
                      "Failed to create a pipe to call %s: %s",
                      progpath, _dbus_strerror (errno));
      _dbus_verbose ("Failed to create a pipe to call %s: %s\n",
                     progpath, _dbus_strerror (errno));
      goto out;
    }


  fflush (stdout);
  fflush (stderr);

  pid = fork ();
  if (pid < 0)
    {
      dbus_set_error (error, _dbus_error_from_errno (errno),
                      "Failed to fork() to call %s: %s",
                      progpath, _dbus_strerror (errno));
      _dbus_verbose ("Failed to fork() to call %s: %s\n",
                     progpath, _dbus_strerror (errno));
      goto out;
    }

  if (pid == 0)
    {

      const char *error_str;

      if (!_dbus_ensure_standard_fds (DBUS_FORCE_STDIN_NULL, &error_str))
        {
          int saved_errno = errno;


          if (write (errors_pipe[WRITE_END], error_str, strlen (error_str)) < 0 ||
              write (errors_pipe[WRITE_END], ": ", 2) < 0)
            {

            }

          error_str = _dbus_strerror (saved_errno);

          if (write (errors_pipe[WRITE_END], error_str, strlen (error_str)) < 0)
            {

            }

          _exit (1);
        }


      close (result_pipe[READ_END]);
      close (errors_pipe[READ_END]);

      if (dup2 (result_pipe[WRITE_END], 1) == -1)
        _exit (1);
      if (dup2 (errors_pipe[WRITE_END], 2) == -1)
        _exit (1);

      _dbus_close_all ();

      sigprocmask (SIG_SETMASK, &old_set, NULL);


      if (progpath[0] == '/')
        {
          execv (progpath, (char * const *) argv);


          if (path_fallback)

            execvp (strrchr (progpath, '/')+1, (char * const *) argv);
        }
      else
        execvp (progpath, (char * const *) argv);


      _exit (1);
    }


  close (result_pipe[WRITE_END]);
  close (errors_pipe[WRITE_END]);
  result_pipe[WRITE_END] = -1;
  errors_pipe[WRITE_END] = -1;

  ret = 0;
  do
    {
      ret = _dbus_read (result_pipe[READ_END], result, 1024);
    }
  while (ret > 0);


  do
    {
      ret = waitpid (pid, &status, 0);
    }
  while (ret == -1 && errno == EINTR);


  if (!WIFEXITED (status) || WEXITSTATUS (status) != 0 )
    {

      DBusString error_message;
      if (!_dbus_string_init (&error_message))
        {
          _DBUS_SET_OOM (error);
          goto out;
        }

      ret = 0;
      do
        {
          ret = _dbus_read (errors_pipe[READ_END], &error_message, 1024);
        }
      while (ret > 0);

      _dbus_string_set_length (result, orig_len);
      if (_dbus_string_get_length (&error_message) > 0)
        dbus_set_error (error, DBUS_ERROR_SPAWN_EXEC_FAILED,
                        "%s terminated abnormally with the following error: %s",
                        progpath, _dbus_string_get_data (&error_message));
      else
        dbus_set_error (error, DBUS_ERROR_SPAWN_EXEC_FAILED,
                        "%s terminated abnormally without any error message",
                        progpath);
      goto out;
    }

  retval = TRUE;

 out:
  sigprocmask (SIG_SETMASK, &old_set, NULL);

  _DBUS_ASSERT_ERROR_XOR_BOOL (error, retval);

  if (result_pipe[0] != -1)
    close (result_pipe[0]);
  if (result_pipe[1] != -1)
    close (result_pipe[1]);
  if (errors_pipe[0] != -1)
    close (errors_pipe[0]);
  if (errors_pipe[1] != -1)
    close (errors_pipe[1]);

  return retval;
}
