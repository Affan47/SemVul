_glcpp_parser_expand_function (glcpp_parser_t *parser,
			       token_node_t *node,
			       token_node_t **last)

{
	macro_t *macro;
	const char *identifier;
	argument_list_t *arguments;
	function_status_t status;
	token_list_t *substituted;
	int parameter_index;

	identifier = node->token->value.str;

	macro = hash_table_find (parser->defines, identifier);

	assert (macro->is_function);

	arguments = _argument_list_create (parser);
	status = _arguments_parse (arguments, node, last);

	switch (status) {
	case FUNCTION_STATUS_SUCCESS:
		break;
	case FUNCTION_NOT_A_FUNCTION:
		return NULL;
	case FUNCTION_UNBALANCED_PARENTHESES:
		glcpp_error (&node->token->location, parser, "Macro %s call has unbalanced parentheses\n", identifier);
		return NULL;
	}


	if (macro->replacements == NULL) {
		ralloc_free (arguments);
		return _token_list_create_with_one_space (parser);
	}

	if (! ((_argument_list_length (arguments) ==
		_string_list_length (macro->parameters)) ||
	       (_string_list_length (macro->parameters) == 0 &&
		_argument_list_length (arguments) == 1 &&
		arguments->head->argument->head == NULL)))
	{
		glcpp_error (&node->token->location, parser,
			      "Error: macro %s invoked with %d arguments (expected %d)\n",
			      identifier,
			      _argument_list_length (arguments),
			      _string_list_length (macro->parameters));
		return NULL;
	}


	substituted = _token_list_create (arguments);

	for (node = macro->replacements->head; node; node = node->next)
	{
		if (node->token->type == IDENTIFIER &&
		    _string_list_contains (macro->parameters,
					   node->token->value.str,
					   &parameter_index))
		{
			token_list_t *argument;
			argument = _argument_list_member_at (arguments,
							     parameter_index);


			if (argument->head) {
				token_list_t *expanded_argument;
				expanded_argument = _token_list_copy (parser,
								      argument);
				_glcpp_parser_expand_token_list (parser,
								 expanded_argument);
				_token_list_append_list (substituted,
							 expanded_argument);
			} else {
				token_t *new_token;

				new_token = _token_create_ival (substituted,
								PLACEHOLDER,
								PLACEHOLDER);
				_token_list_append (substituted, new_token);
			}
		} else {
			_token_list_append (substituted, node->token);
		}
	}


	_token_list_trim_trailing_space (substituted);

	_glcpp_parser_apply_pastes (parser, substituted);

	return substituted;
}
