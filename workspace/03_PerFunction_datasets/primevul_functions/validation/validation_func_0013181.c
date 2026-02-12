push_func_var (data)
     PTR_T data;
{
  SHELL_VAR *var, *v;

  var = (SHELL_VAR *)data;

  if (tempvar_p (var) && (posixly_correct || (var->attributes & att_propagate)))
    {


      if ((vc_isfuncenv (shell_variables) || vc_istempenv (shell_variables)) && shell_variables->table == 0)
	shell_variables->table = hash_create (0);

      v = bind_variable_internal (var->name, value_cell (var), shell_variables->table, 0, 0);
      if (shell_variables == global_variables)
	var->attributes &= ~(att_tempvar|att_propagate);
      else
	shell_variables->flags |= VC_HASTMPVAR;
      v->attributes |= var->attributes;
    }
  else
    stupidly_hack_special_variables (var->name);

  dispose_variable (var);
}
