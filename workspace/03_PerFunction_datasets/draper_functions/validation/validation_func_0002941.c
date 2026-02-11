print_banner(int argc, char **argv,
		  char *name, char *version, char *date,
		  BOOL as_comments)
{
  int i;
  char *com = (as_comments ? "% " : "");

  if (!as_comments)
    print_separator(stdout, name, FALSE);

  printf("%s%s (%d) version %s, %s.\n",
	 com, name, get_bits(), version, date);
  printf("%sProcess %d was started by %s on %s,\n%s%s",
	 com, my_process_id(), username(), hostname(), com, get_date());

  printf("%sThe command was \"", com);
  for(i = 0; i < argc; i++)
    printf("%s%s", argv[i], (i < argc-1 ? " " : ""));
  printf("\".\n");

  if (!as_comments)
    print_separator(stdout, "end of head", FALSE);
  fflush(stdout);
}
