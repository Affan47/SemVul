bind_variable (name, value, flags)
     const char *name;
     char *value;
     int flags;
{
  SHELL_VAR *v;
  VAR_CONTEXT *vc;

  if (shell_variables == 0)
    create_variable_tables ();


  if (temporary_env)
    bind_tempenv_variable (name, value);


  for (vc = shell_variables; vc; vc = vc->down)
    {
      if (vc_isfuncenv (vc) || vc_isbltnenv (vc))
	{
	  v = hash_lookup (name, vc->table);
	  if (v)
	    return (bind_variable_internal (name, value, vc->table, 0, flags));
	}
    }
  return (bind_variable_internal (name, value, global_variables->table, 0, flags));
}
