find_variable_internal (name, force_tempenv)
     const char *name;
     int force_tempenv;
{
  SHELL_VAR *var;
  int search_tempenv;

  var = (SHELL_VAR *)NULL;


  search_tempenv = force_tempenv || (expanding_redir == 0 && subshell_environment);

  if (search_tempenv && temporary_env)
    var = hash_lookup (name, temporary_env);

  if (var == 0)
    var = var_lookup (name, shell_variables);

  if (var == 0)
    return ((SHELL_VAR *)NULL);

  return (var->dynamic_value ? (*(var->dynamic_value)) (var) : var);
}
