exim_usage(uschar *progname)
{


if (Ustrcmp(progname, US"-mailq") == 0)
  exim_fail(
    "mailq - list the contents of the mail queue\n\n"
    "For a list of options, see the Exim documentation.\n");


exim_fail(
  "Exim is a Mail Transfer Agent. It is normally called by Mail User Agents,\n"
  "not directly from a shell command line. Options and/or arguments control\n"
  "what it does when called. For a list of options, see the Exim documentation.\n");
}
