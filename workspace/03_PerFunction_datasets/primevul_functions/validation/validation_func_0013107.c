fapply (func)
     sh_var_map_func_t *func;
{
  SHELL_VAR **list;

  list = map_over_funcs (func);
  if (list )
    sort_variables (list);
  return (list);
}
