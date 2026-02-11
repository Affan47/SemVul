parse_client6_iaaddr_statement(struct parse *cfile)
{
	struct option_cache *oc = NULL;
	struct dhc6_addr *addr;
	const char *val;
	int token, no_semi;

	addr = dmalloc(sizeof(*addr), MDL);
	if (addr == NULL) {
		parse_warn(cfile, "Unable to allocate IAADDR state.");
		skip_to_semi(cfile);
		return NULL;
	}


	if (!parse_ip6_addr(cfile, &addr->address)) {
		skip_to_semi(cfile);
		dfree(addr, MDL);
		return NULL;
	}

	token = next_token(NULL, NULL, cfile);
	if (token != LBRACE) {
		parse_warn(cfile, "Expecting open curly bracket.");
		skip_to_semi(cfile);
		dfree(addr, MDL);
		return NULL;
	}

	option_state_allocate(&addr->options, MDL);
	if (addr->options == NULL) {
		parse_warn(cfile, "Unable to allocate option state.");
		skip_to_semi(cfile);
		dfree(addr, MDL);
		return NULL;
	}

	token = next_token(&val, NULL, cfile);
	while (token != RBRACE) {
		no_semi = 0;

		switch (token) {
		      case STARTS:
			token = next_token(&val, NULL, cfile);
			if (token == NUMBER) {
				addr->starts = atoi(val);
			} else {
				parse_warn(cfile, "Expecting a number.");
				skip_to_semi(cfile);
				no_semi = 1;
			}
			break;

		      case PREFERRED_LIFE:
			token = next_token(&val, NULL, cfile);
			if (token == NUMBER) {
				addr->preferred_life = atoi(val);
			} else {
				parse_warn(cfile, "Expecting a number.");
				skip_to_semi(cfile);
				no_semi = 1;
			}
			break;

		      case MAX_LIFE:
			token = next_token(&val, NULL, cfile);
			if (token == NUMBER) {
				addr->max_life = atoi(val);
			} else {
				parse_warn(cfile, "Expecting a number.");
				skip_to_semi(cfile);
				no_semi = 1;
			}
			break;

		      case OPTION:
			if (parse_option_decl(&oc, cfile)) {
				save_option(oc->option->universe,
					    addr->options, oc);
				option_cache_dereference(&oc, MDL);
			}
			no_semi = 1;
			break;

		      default:
			parse_warn(cfile, "Unexpected token.");
			skip_to_rbrace(cfile, 1);
			no_semi = 1;
			break;
		}

		if (!no_semi)
			parse_semi(cfile);

		token = next_token(&val, NULL, cfile);
		if (token == END_OF_FILE) {
			parse_warn(cfile, "Unexpected end of file.");
			break;
		}
	}

	return addr;
}
