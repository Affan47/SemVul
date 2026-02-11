unmodified_parm_or_parm_agg_item (struct ipa_node_params *info,
				  gimple stmt, tree op, int *index_p,
				  struct agg_position_info *aggpos)
{
  tree res = unmodified_parm_1 (stmt, op);

  gcc_checking_assert (aggpos);
  if (res)
    {
      *index_p = ipa_get_param_decl_index (info, res);
      if (*index_p < 0)
	return false;
      aggpos->agg_contents = false;
      aggpos->by_ref = false;
      return true;
    }

  if (TREE_CODE (op) == SSA_NAME)
    {
      if (SSA_NAME_IS_DEFAULT_DEF (op)
	  || !gimple_assign_single_p (SSA_NAME_DEF_STMT (op)))
	return false;
      stmt = SSA_NAME_DEF_STMT (op);
      op = gimple_assign_rhs1 (stmt);
      if (!REFERENCE_CLASS_P (op))
	return unmodified_parm_or_parm_agg_item (info, stmt, op, index_p,
						 aggpos);
    }

  aggpos->agg_contents = true;
  return ipa_load_from_parm_agg (info, stmt, op, index_p, &aggpos->offset,
				 &aggpos->by_ref);
}
