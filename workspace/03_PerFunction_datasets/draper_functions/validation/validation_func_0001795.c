cp_parser_constructor_declarator_p (cp_parser *parser, bool friend_p)
{
  bool constructor_p;
  tree nested_name_specifier;
  cp_token *next_token;


  if (parser->in_function_body)
    return false;

  next_token = cp_lexer_peek_token (parser->lexer);
  if (next_token->type != CPP_NAME
      && next_token->type != CPP_SCOPE
      && next_token->type != CPP_NESTED_NAME_SPECIFIER
      && next_token->type != CPP_TEMPLATE_ID)
    return false;


  cp_parser_parse_tentatively (parser);

  constructor_p = true;


  cp_parser_global_scope_opt (parser,
			      false);

  nested_name_specifier
    = (cp_parser_nested_name_specifier_opt (parser,
					    false,
					    false,
					    false,
					    false));


  if (!nested_name_specifier &&
      (!at_class_scope_p () || !TYPE_BEING_DEFINED (current_class_type)
       || friend_p))
    constructor_p = false;
  else if (nested_name_specifier == error_mark_node)
    constructor_p = false;


  if (constructor_p && nested_name_specifier
      && CLASS_TYPE_P (nested_name_specifier))
    {
      tree id = cp_parser_unqualified_id (parser,
					  false,
					  false,
					  true,
					  false);
      if (is_overloaded_fn (id))
	id = DECL_NAME (get_first_fn (id));
      if (!constructor_name_p (id, nested_name_specifier))
	constructor_p = false;
    }


  else if (constructor_p)
    {


      tree type_decl;
      type_decl = cp_parser_class_name (parser,
					false,
					false,
					none_type,
					false,
					false,
					false);

      constructor_p = !cp_parser_error_occurred (parser);


      if (constructor_p
	  && !cp_parser_require (parser, CPP_OPEN_PAREN, RT_OPEN_PAREN))
	constructor_p = false;

      if (constructor_p
	  && cp_lexer_next_token_is_not (parser->lexer, CPP_CLOSE_PAREN)
	  && cp_lexer_next_token_is_not (parser->lexer, CPP_ELLIPSIS)


	  && !cp_lexer_next_token_is_decl_specifier_keyword (parser->lexer))
	{
	  tree type;
	  tree pushed_scope = NULL_TREE;
	  unsigned saved_num_template_parameter_lists;


	  if (current_class_type)
	    type = NULL_TREE;
	  else
	    {
	      type = TREE_TYPE (type_decl);
	      if (TREE_CODE (type) == TYPENAME_TYPE)
		{
		  type = resolve_typename_type (type,
						false);
		  if (TREE_CODE (type) == TYPENAME_TYPE)
		    {
		      cp_parser_abort_tentative_parse (parser);
		      return false;
		    }
		}
	      pushed_scope = push_scope (type);
	    }


	  saved_num_template_parameter_lists
	    = parser->num_template_parameter_lists;
	  parser->num_template_parameter_lists = 0;


	  cp_parser_type_specifier (parser,
				    CP_PARSER_FLAGS_NONE,
				    NULL,
				    true,
				    NULL,
				    NULL);

	  parser->num_template_parameter_lists
	    = saved_num_template_parameter_lists;


	  if (pushed_scope)
	    pop_scope (pushed_scope);

	  constructor_p = !cp_parser_error_occurred (parser);
	}
    }


  cp_parser_abort_tentative_parse (parser);

  return constructor_p;
}
