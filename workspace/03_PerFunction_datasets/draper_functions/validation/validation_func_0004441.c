build_dynamic_cast (tree type, tree expr, tsubst_flags_t complain)
{
  tree r;

  if (type == error_mark_node || expr == error_mark_node)
    return error_mark_node;

  if (processing_template_decl)
    {
      expr = build_min (DYNAMIC_CAST_EXPR, type, expr);
      TREE_SIDE_EFFECTS (expr) = 1;
      return convert_from_reference (expr);
    }

  r = convert_from_reference (build_dynamic_cast_1 (type, expr, complain));
  if (r != error_mark_node)
    maybe_warn_about_useless_cast (type, expr, complain);
  return r;
}
