grab_command(void)
{
  unsigned i;
  unsigned len;

  unsigned best;
  match_type best_match = match_None;
  unsigned best_len = 0;
  BOOL found = FALSE;
  BOOL ambig = FALSE;

  while(isspace(lex_expression[lex_offset]))
    lex_offset++;

  for(i = 0; i < sizeof(infix_commands) / sizeof(*infix_commands); i++) {
    switch(command_matches(infix_commands[i].name, lex_expression + lex_offset, &len)) {
    case match_Complete:
      if(len > best_len || best_match != match_Complete) {
	best = i;
	best_match = match_Complete;
	best_len = len;
	found = TRUE;
      }
      break;

    case match_Partial:
      if(best_match != match_Complete) {
	if(found)
	  ambig = TRUE;
	best = i;
	best_match = match_Partial;
	best_len = len;
	found = TRUE;
      }

    case match_None:
      ;
    }
  }

  if(ambig && best_match != match_Complete) {
    infix_print_string("Ambiguous command.\n");
    return 0;
  }

  if(found) {
    lex_offset += best_len;
    return infix_commands[best].token;
  }

  infix_print_string("Undefined command.\n");
  return 0;
}
