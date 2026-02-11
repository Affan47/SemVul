check_tcl_fil(char *cmd, int idx, char *args)
{
  int x;
  char s[5];
  struct flag_record fr = { FR_GLOBAL | FR_CHAN, 0, 0, 0, 0, 0 };

  get_user_flagrec(dcc[idx].user, &fr, dcc[idx].u.file->chat->con_chan);
  sprintf(s, "%ld", dcc[idx].sock);
  Tcl_SetVar(interp, "_fil1", dcc[idx].nick, 0);
  Tcl_SetVar(interp, "_fil2", s, 0);
  Tcl_SetVar(interp, "_fil3", args, 0);
  x = check_tcl_bind(H_fil, cmd, &fr, " $_fil1 $_fil2 $_fil3",
                     MATCH_PARTIAL | BIND_USE_ATTR | BIND_HAS_BUILTINS);
  if (x == BIND_AMBIGUOUS) {
    dprintf(idx, "Ambiguous command.\n");
    return 0;
  }
  if (x == BIND_NOMATCH) {
    dprintf(idx, "What?  You need 'help'\n");
    return 0;
  }


  if (x == BIND_QUIT)
    return 1;

  if (x == BIND_EXEC_LOG)
    putlog(LOG_FILES, "*", "#%s# files: %s %s", dcc[idx].nick, cmd, args);
  return 0;
}
