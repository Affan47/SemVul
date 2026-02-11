tcl_die STDVAR
{
  char s[1024];

  BADARGS(1, 2, " ?reason?");

  if (argc == 2) {
    egg_snprintf(s, sizeof s, "BOT SHUTDOWN (%s)", argv[1]);
    strncpyz(quit_msg, argv[1], 1024);
  } else {
    strncpyz(s, "BOT SHUTDOWN (No reason)", sizeof s);
    quit_msg[0] = 0;
  }
  kill_bot(s, quit_msg[0] ? quit_msg : "EXIT");
  return TCL_OK;
}
