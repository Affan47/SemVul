find_loc_in_1pdv (rtx loc, variable var, htab_t vars)
{
  location_chain node;
  enum rtx_code loc_code;

  if (!var)
    return NULL;

  gcc_checking_assert (var->onepart);

  if (!var->n_var_parts)
    return NULL;

  gcc_checking_assert (loc != dv_as_opaque (var->dv));

  loc_code = GET_CODE (loc);
  for (node = var->var_part[0].loc_chain; node; node = node->next)
    {
      decl_or_value dv;
      variable rvar;

      if (GET_CODE (node->loc) != loc_code)
	{
	  if (GET_CODE (node->loc) != VALUE)
	    continue;
	}
      else if (loc == node->loc)
	return node;
      else if (loc_code != VALUE)
	{
	  if (rtx_equal_p (loc, node->loc))
	    return node;
	  continue;
	}


      if (dv_is_value_p (var->dv)
	  && !canon_value_cmp (node->loc, dv_as_value (var->dv)))
	{

	  while (node->next && GET_CODE (node->next->loc) == VALUE)
	    {
	      node = node->next;
	      gcc_checking_assert (!canon_value_cmp (node->loc,
						     dv_as_value (var->dv)));
	      if (loc == node->loc)
		return node;
	    }
	  continue;
	}

      gcc_checking_assert (node == var->var_part[0].loc_chain);
      gcc_checking_assert (!node->next);

      dv = dv_from_value (node->loc);
      rvar = (variable) htab_find_with_hash (vars, dv, dv_htab_hash (dv));
      return find_loc_in_1pdv (loc, rvar, vars);
    }


  return NULL;
}
