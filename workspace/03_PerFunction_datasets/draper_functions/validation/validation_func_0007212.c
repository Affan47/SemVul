list_some_builtins (filter)
     int filter;
{
  register int i;

  for (i = 0; i < num_shell_builtins; i++)
    {
      if (shell_builtins[i].function == 0 || (shell_builtins[i].flags & BUILTIN_DELETED))
	continue;

      if ((filter & SPECIAL) &&
	  (shell_builtins[i].flags & SPECIAL_BUILTIN) == 0)
	continue;

      if ((filter & ENABLED) && (shell_builtins[i].flags & BUILTIN_ENABLED))
	printf ("enable %s\n", shell_builtins[i].name);
      else if ((filter & DISABLED) &&
	       ((shell_builtins[i].flags & BUILTIN_ENABLED) == 0))
	printf ("enable -n %s\n", shell_builtins[i].name);
    }
}
