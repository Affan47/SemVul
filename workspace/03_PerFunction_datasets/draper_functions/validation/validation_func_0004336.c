cp_parser_conversion_function_id (cp_parser* parser)
{
  tree type;
  tree saved_scope;
  tree saved_qualifying_scope;
  tree saved_object_scope;
  bool pop_p = false;


  if (!cp_parser_require_keyword (parser, RID_OPERATOR, "`operator'"))
    return error_mark_node;


  saved_scope = parser->scope;
  saved_qualifying_scope = parser->qualifying_scope;
  saved_object_scope = parser->object_scope;


  if (saved_scope)
    pop_p = push_scope (saved_scope);

  type = cp_parser_conversion_type_id (parser);

  if (pop_p)
    pop_scope (saved_scope);

  parser->scope = saved_scope;
  parser->qualifying_scope = saved_qualifying_scope;
  parser->object_scope = saved_object_scope;

  if (type == error_mark_node)
    return error_mark_node;
  return mangle_conv_op_name_for_type (type);
}
