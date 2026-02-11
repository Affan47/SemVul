cp_parser_id_expression (cp_parser *parser,
			 bool template_keyword_p,
			 bool check_dependency_p,
			 bool *template_p,
			 bool declarator_p,
			 bool optional_p)
{
  bool global_scope_p;
  bool nested_name_specifier_p;


  if (template_p)
    *template_p = template_keyword_p;


  global_scope_p
    = (cp_parser_global_scope_opt (parser, false)
       != NULL_TREE);

  nested_name_specifier_p
    = (cp_parser_nested_name_specifier_opt (parser,
					    false,
					    check_dependency_p,
					    false,
					    declarator_p)
       != NULL_TREE);


  if (nested_name_specifier_p)
    {
      tree saved_scope;
      tree saved_object_scope;
      tree saved_qualifying_scope;
      tree unqualified_id;
      bool is_template;


      if (!template_p)
	template_p = &is_template;
      *template_p = cp_parser_optional_template_keyword (parser);


      saved_scope = parser->scope;
      saved_object_scope = parser->object_scope;
      saved_qualifying_scope = parser->qualifying_scope;

      unqualified_id = cp_parser_unqualified_id (parser, *template_p,
						 check_dependency_p,
						 declarator_p,
						 false);

      parser->scope = saved_scope;
      parser->object_scope = saved_object_scope;
      parser->qualifying_scope = saved_qualifying_scope;

      return unqualified_id;
    }


  else if (global_scope_p)
    {
      cp_token *token;
      tree id;


      token = cp_lexer_peek_token (parser->lexer);


      if (token->type == CPP_NAME
	  && !cp_parser_nth_token_starts_template_argument_list_p
	       (parser, 2))
	return cp_parser_identifier (parser);

      cp_parser_parse_tentatively (parser);

      id = cp_parser_template_id (parser,
				  false,
				  true,
				  none_type,
				  declarator_p);

      if (cp_parser_parse_definitely (parser))
	return id;


      token = cp_lexer_peek_token (parser->lexer);

      switch (token->type)
	{
	case CPP_NAME:
	  return cp_parser_identifier (parser);

	case CPP_KEYWORD:
	  if (token->keyword == RID_OPERATOR)
	    return cp_parser_operator_function_id (parser);


	default:
	  cp_parser_error (parser, "expected id-expression");
	  return error_mark_node;
	}
    }
  else
    return cp_parser_unqualified_id (parser, template_keyword_p,
				     true,
				     declarator_p,
				     optional_p);
}
