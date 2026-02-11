c_parser_objc_keywordexpr (c_parser *parser)
{
  tree ret;
  VEC(tree,gc) *expr_list = c_parser_expr_list (parser, true, true, NULL);
  if (VEC_length (tree, expr_list) == 1)
    {


      ret = VEC_index (tree, expr_list, 0);
    }
  else
    {

      ret = build_tree_list_vec (expr_list);
    }
  release_tree_vector (expr_list);
  return ret;
}
