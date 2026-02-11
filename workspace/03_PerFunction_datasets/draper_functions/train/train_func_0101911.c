is_unused_scalar_param (tree parm)
{
  tree name;
  return (is_gimple_reg (parm)
	  && (!(name = gimple_default_def (cfun, parm))
	      || has_zero_uses (name)));
}
