it_init_builtins (itp)
     ITEMLIST *itp;
{
  STRINGLIST *sl;
  register int i, n;

  sl = strlist_create (num_shell_builtins);
  for (i = n = 0; i < num_shell_builtins; i++)
    if (shell_builtins[i].function)
      sl->list[n++] = shell_builtins[i].name;
  sl->list[sl->list_len = n] = (char *)NULL;
  itp->flags |= LIST_DONTFREEMEMBERS;
  itp->slist = sl;
  return 0;
}
