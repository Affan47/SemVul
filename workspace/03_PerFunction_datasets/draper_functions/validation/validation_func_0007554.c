get_replacement_map (tree value, tree parm)
{
  tree req_type = TREE_TYPE (parm);
  struct ipa_replace_map *replace_map;

  if (!useless_type_conversion_p (req_type, TREE_TYPE (value)))
    {
      if (fold_convertible_p (req_type, value))
	value = fold_build1 (NOP_EXPR, req_type, value);
      else if (TYPE_SIZE (req_type) == TYPE_SIZE (TREE_TYPE (value)))
	value = fold_build1 (VIEW_CONVERT_EXPR, req_type, value);
      else
	{
	  if (dump_file)
	    {
	      fprintf (dump_file, "    const ");
	      print_generic_expr (dump_file, value, 0);
	      fprintf (dump_file, "  can't be converted to param ");
	      print_generic_expr (dump_file, parm, 0);
	      fprintf (dump_file, "\n");
	    }
	  return NULL;
	}
    }

  replace_map = ggc_alloc_ipa_replace_map ();
  if (dump_file)
    {
      fprintf (dump_file, "    replacing param ");
      print_generic_expr (dump_file, parm, 0);
      fprintf (dump_file, " with const ");
      print_generic_expr (dump_file, value, 0);
      fprintf (dump_file, "\n");
    }
  replace_map->old_tree = parm;
  replace_map->new_tree = value;
  replace_map->replace_p = true;
  replace_map->ref_p = false;

  return replace_map;
}
