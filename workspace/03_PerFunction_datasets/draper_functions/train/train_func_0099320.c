Read_Term(StmInf *pstm, int parse_end_of_term)
{
  int jmp_val;
  WamWord term;
  int save_use_le_prompt = use_le_prompt;

  use_le_prompt = 1;

  parse_nb_var = 0;
  last_read_line = -1;

  pstm_i = pstm;

  tok_present = FALSE;
  Save_Machine_Regs(buff_save_machine_regs);

  jmp_val = setjmp(jumper);

  Restore_Machine_Regs(buff_save_machine_regs);

  if (jmp_val == 0)
    {
      term = Parse_Term(MAX_PREC, GENERAL_TERM, COMMA_ANY);
      Read_Next_Token(COMMA_ANY);

      if (term == NOT_A_WAM_WORD)
	{
	  if (token.type == TOKEN_END_OF_FILE)
	    {
	      term = Put_Atom(atom_end_of_file);
	      goto finish;
	    }
	  else
	    Parse_Error("expression expected");
	}

      if (parse_end_of_term == PARSE_END_OF_TERM_DOT)
	{
	  if (token.type == TOKEN_FULL_STOP)
	    goto finish;
	  else
	    {
	      Unget_Token;
	      Parse_Error(". or operator expected after expression");
	    }
	}

      if (token.type == TOKEN_END_OF_FILE)
	goto finish;
      else
	{
	  Unget_Token;
	  Parse_Error("eof or operator expected after expression");
	}
    }
  else
    {
      Restore_Machine_Regs(buff_save_machine_regs);
      term = NOT_A_WAM_WORD;
    }

finish:
  use_le_prompt = save_use_le_prompt;
  return term;
}
