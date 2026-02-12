push_exported_var (data)
     PTR_T data;
{
  SHELL_VAR *var, *v;

  var = (SHELL_VAR *)data;


#if 0
  if (exported_p (var) || (var->attributes & att_propagate))
#else
  if (tempvar_p (var) && exported_p (var) && (var->attributes & att_propagate))
#endif
    {
      var->attributes &= ~att_tempvar;
      v = bind_variable_internal (var->name, value_cell (var), shell_variables->table, 0, 0);
      if (shell_variables == global_variables)
	var->attributes &= ~att_propagate;
      v->attributes |= var->attributes;
    }
  else
    stupidly_hack_special_variables (var->name);

  dispose_variable (var);
}
