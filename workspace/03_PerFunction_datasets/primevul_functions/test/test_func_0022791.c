static int lex_one_token(YYSTYPE *yylval, THD *thd)
{
  uchar UNINIT_VAR(c);
  bool comment_closed;
  int	tokval, result_state;
  uint length;
  enum my_lex_states state;
  Lex_input_stream *lip= & thd->m_parser_state->m_lip;
  LEX *lex= thd->lex;
  CHARSET_INFO *const cs= thd->charset();
  const uchar *const state_map= cs->state_map;
  const uchar *const ident_map= cs->ident_map;

  lip->yylval=yylval;

  lip->start_token();
  state=lip->next_state;
  lip->next_state=MY_LEX_OPERATOR_OR_IDENT;
  for (;;)
  {
    switch (state) {
    case MY_LEX_OPERATOR_OR_IDENT:
    case MY_LEX_START:

      while(state_map[c= lip->yyPeek()] == MY_LEX_SKIP)
      {
	if (c == '\n')
	  lip->yylineno++;

        lip->yySkip();
      }


      lip->restart_token();
      c= lip->yyGet();
      state= (enum my_lex_states) state_map[c];
      break;
    case MY_LEX_ESCAPE:
      if (!lip->eof() && lip->yyGet() == 'N')
      {
	yylval->lex_str.str=(char*) "\\N";
	yylval->lex_str.length=2;
	return NULL_SYM;
      }

    case MY_LEX_CHAR:
    case MY_LEX_SKIP:
      if (c != ')')
	lip->next_state= MY_LEX_START;
      return((int) c);

    case MY_LEX_MINUS_OR_COMMENT:
      if (lip->yyPeek() == '-' &&
          (my_isspace(cs,lip->yyPeekn(1)) ||
           my_iscntrl(cs,lip->yyPeekn(1))))
      {
        state=MY_LEX_COMMENT;
        break;
      }
      lip->next_state= MY_LEX_START;
      return((int) c);

    case MY_LEX_PLACEHOLDER:


      lip->next_state= MY_LEX_START;
      if (lip->stmt_prepare_mode && !ident_map[(uchar) lip->yyPeek()])
        return(PARAM_MARKER);
      return((int) c);

    case MY_LEX_COMMA:
      lip->next_state= MY_LEX_START;


      lip->restart_token();
      return((int) c);

    case MY_LEX_IDENT_OR_NCHAR:
    {
      uint sep;
      if (lip->yyPeek() != '\'')
      {
	state= MY_LEX_IDENT;
	break;
      }

      lip->yySkip();
      if (lip->get_text(&yylval->lex_str, (sep= lip->yyGetLast()), 2, 1))
      {
	state= MY_LEX_CHAR;
	break;
      }

      lip->body_utf8_append(lip->m_cpp_text_start);
      lip->body_utf8_append_escape(thd, &yylval->lex_str,
                                   national_charset_info,
                                   lip->m_cpp_text_end, sep);

      lex->text_string_is_7bit= (lip->tok_bitmap & 0x80) ? 0 : 1;
      return(NCHAR_STRING);
    }
    case MY_LEX_IDENT_OR_HEX:
      if (lip->yyPeek() == '\'')
      {
	state= MY_LEX_HEX_NUMBER;
	break;
      }

    case MY_LEX_IDENT_OR_BIN:
      if (lip->yyPeek() == '\'')
      {
        state= MY_LEX_BIN_NUMBER;
        break;
      }

    case MY_LEX_IDENT:
      const char *start;
#if defined(USE_MB) && defined(USE_MB_IDENT)
      if (use_mb(cs))
      {
	result_state= IDENT_QUOTED;
        int char_length= my_charlen(cs, lip->get_ptr() - 1,
                                        lip->get_end_of_query());
        if (char_length <= 0)
        {
          state= MY_LEX_CHAR;
          continue;
        }
        lip->skip_binary(char_length - 1);

        while (ident_map[c=lip->yyGet()])
        {
          char_length= my_charlen(cs, lip->get_ptr() - 1,
                                      lip->get_end_of_query());
          if (char_length <= 0)
            break;
          lip->skip_binary(char_length - 1);
        }
      }
      else
#endif
      {
        for (result_state= c;
             ident_map[(uchar) (c= lip->yyGet())];
             result_state|= c)
          ;

        result_state= result_state & 0x80 ? IDENT_QUOTED : IDENT;
      }
      length= lip->yyLength();
      start= lip->get_ptr();
      if (lip->ignore_space)
      {


        for (; state_map[(uchar) c] == MY_LEX_SKIP ; c= lip->yyGet())
        {
          if (c == '\n')
            lip->yylineno++;
        }
      }
      if (start == lip->get_ptr() && c == '.' &&
          ident_map[(uchar) lip->yyPeek()])
	lip->next_state=MY_LEX_IDENT_SEP;
      else
      {
        lip->yyUnget();
	if ((tokval = find_keyword(lip, length, c == '(')))
	{
	  lip->next_state= MY_LEX_START;
	  return(tokval);
	}
        lip->yySkip();
      }
      yylval->lex_str=get_token(lip, 0, length);


      if (yylval->lex_str.str[0] == '_')
      {
        CHARSET_INFO *cs= get_charset_by_csname(yylval->lex_str.str + 1,
                                                MY_CS_PRIMARY, MYF(0));
        if (cs)
        {
          yylval->charset= cs;
          lip->m_underscore_cs= cs;

          lip->body_utf8_append(lip->m_cpp_text_start,
                                lip->get_cpp_tok_start() + length);
          return(UNDERSCORE_CHARSET);
        }
      }

      lip->body_utf8_append(lip->m_cpp_text_start);

      lip->body_utf8_append_ident(thd, &yylval->lex_str, lip->m_cpp_text_end);

      return(result_state);

    case MY_LEX_IDENT_SEP:
      yylval->lex_str.str= (char*) lip->get_ptr();
      yylval->lex_str.length= 1;
      c= lip->yyGet();
      lip->next_state= MY_LEX_IDENT_START;
      if (!ident_map[(uchar) lip->yyPeek()])
	lip->next_state= MY_LEX_START;
      return((int) c);

    case MY_LEX_NUMBER_IDENT:
      if (lip->yyGetLast() == '0')
      {
        c= lip->yyGet();
        if (c == 'x')
        {
          while (my_isxdigit(cs,(c = lip->yyGet()))) ;
          if ((lip->yyLength() >= 3) && !ident_map[c])
          {

            yylval->lex_str=get_token(lip, 2, lip->yyLength()-2);
            return (HEX_NUM);
          }
          lip->yyUnget();
          state= MY_LEX_IDENT_START;
          break;
        }
        else if (c == 'b')
        {
          while ((c= lip->yyGet()) == '0' || c == '1')
            ;
          if ((lip->yyLength() >= 3) && !ident_map[c])
          {

            yylval->lex_str= get_token(lip, 2, lip->yyLength()-2);
            return (BIN_NUM);
          }
          lip->yyUnget();
          state= MY_LEX_IDENT_START;
          break;
        }
        lip->yyUnget();
      }

      while (my_isdigit(cs, (c = lip->yyGet()))) ;
      if (!ident_map[c])
      {
	state=MY_LEX_INT_OR_REAL;
	break;
      }
      if (c == 'e' || c == 'E')
      {

        if (my_isdigit(cs,lip->yyPeek()) ||
            (c=(lip->yyGet())) == '+' || c == '-')
	{
          if (my_isdigit(cs,lip->yyPeek()))
	  {
            lip->yySkip();
            while (my_isdigit(cs,lip->yyGet())) ;
            yylval->lex_str=get_token(lip, 0, lip->yyLength());
	    return(FLOAT_NUM);
	  }
	}
        lip->yyUnget();
      }

    case MY_LEX_IDENT_START:
      result_state= IDENT;
#if defined(USE_MB) && defined(USE_MB_IDENT)
      if (use_mb(cs))
      {
	result_state= IDENT_QUOTED;
        while (ident_map[c=lip->yyGet()])
        {
          int char_length= my_charlen(cs, lip->get_ptr() - 1,
                                          lip->get_end_of_query());
          if (char_length <= 0)
            break;
          lip->skip_binary(char_length - 1);
        }
      }
      else
#endif
      {
        for (result_state=0; ident_map[c= lip->yyGet()]; result_state|= c)
          ;

        result_state= result_state & 0x80 ? IDENT_QUOTED : IDENT;
      }
      if (c == '.' && ident_map[(uchar) lip->yyPeek()])
	lip->next_state=MY_LEX_IDENT_SEP;

      yylval->lex_str= get_token(lip, 0, lip->yyLength());

      lip->body_utf8_append(lip->m_cpp_text_start);

      lip->body_utf8_append_ident(thd, &yylval->lex_str, lip->m_cpp_text_end);

      return(result_state);

    case MY_LEX_USER_VARIABLE_DELIMITER:
    {
      uint double_quotes= 0;
      char quote_char= c;
      while ((c=lip->yyGet()))
      {
        int var_length= my_charlen(cs, lip->get_ptr() - 1,
                                       lip->get_end_of_query());
        if (var_length == 1)
	{
	  if (c == quote_char)
	  {
            if (lip->yyPeek() != quote_char)
	      break;
            c=lip->yyGet();
	    double_quotes++;
	    continue;
	  }
	}
#ifdef USE_MB
        else if (var_length > 1)
        {
          lip->skip_binary(var_length - 1);
        }
#endif
      }
      if (double_quotes)
	yylval->lex_str=get_quoted_token(lip, 1,
                                         lip->yyLength() - double_quotes -1,
					 quote_char);
      else
        yylval->lex_str=get_token(lip, 1, lip->yyLength() -1);
      if (c == quote_char)
        lip->yySkip();
      lip->next_state= MY_LEX_START;

      lip->body_utf8_append(lip->m_cpp_text_start);

      lip->body_utf8_append_ident(thd, &yylval->lex_str, lip->m_cpp_text_end);

      return(IDENT_QUOTED);
    }
    case MY_LEX_INT_OR_REAL:
      if (c != '.')
      {
        yylval->lex_str=get_token(lip, 0, lip->yyLength());
	return int_token(yylval->lex_str.str, (uint) yylval->lex_str.length);
      }

    case MY_LEX_REAL:
      while (my_isdigit(cs,c = lip->yyGet())) ;

      if (c == 'e' || c == 'E')
      {
        c = lip->yyGet();
	if (c == '-' || c == '+')
          c = lip->yyGet();
	if (!my_isdigit(cs,c))
	{
	  return (ABORT_SYM);
	}
        while (my_isdigit(cs,lip->yyGet())) ;
        yylval->lex_str=get_token(lip, 0, lip->yyLength());
	return(FLOAT_NUM);
      }
      yylval->lex_str=get_token(lip, 0, lip->yyLength());
      return(DECIMAL_NUM);

    case MY_LEX_HEX_NUMBER:
      lip->yySkip();
      while (my_isxdigit(cs, (c= lip->yyGet()))) ;
      if (c != '\'')
        return(ABORT_SYM);
      lip->yySkip();
      length= lip->yyLength();
      if ((length % 2) == 0)
        return(ABORT_SYM);
      yylval->lex_str=get_token(lip,
                                2,
                                length-3);
      return HEX_STRING;

    case MY_LEX_BIN_NUMBER:
      lip->yySkip();
      while ((c= lip->yyGet()) == '0' || c == '1')
        ;
      if (c != '\'')
        return(ABORT_SYM);
      lip->yySkip();
      length= lip->yyLength();
      yylval->lex_str= get_token(lip,
                                 2,
                                 length-3);
      return (BIN_NUM);

    case MY_LEX_CMP_OP:
      lip->next_state= MY_LEX_START;
      if (state_map[(uchar) lip->yyPeek()] == MY_LEX_CMP_OP ||
          state_map[(uchar) lip->yyPeek()] == MY_LEX_LONG_CMP_OP)
      {
        lip->yySkip();
        if ((tokval= find_keyword(lip, 2, 0)))
          return(tokval);
        lip->yyUnget();
      }
      return(c);

    case MY_LEX_LONG_CMP_OP:
      lip->next_state= MY_LEX_START;
      if (state_map[(uchar) lip->yyPeek()] == MY_LEX_CMP_OP ||
          state_map[(uchar) lip->yyPeek()] == MY_LEX_LONG_CMP_OP)
      {
        lip->yySkip();
        if (state_map[(uchar) lip->yyPeek()] == MY_LEX_CMP_OP)
        {
          lip->yySkip();
          if ((tokval= find_keyword(lip, 3, 0)))
            return(tokval);
          lip->yyUnget();
        }
        if ((tokval= find_keyword(lip, 2, 0)))
          return(tokval);
        lip->yyUnget();
      }
      return(c);

    case MY_LEX_BOOL:
      if (c != lip->yyPeek())
      {
	state=MY_LEX_CHAR;
	break;
      }
      lip->yySkip();
      tokval = find_keyword(lip,2,0);
      lip->next_state= MY_LEX_START;
      return(tokval);

    case MY_LEX_STRING_OR_DELIMITER:
      if (thd->variables.sql_mode & MODE_ANSI_QUOTES)
      {
	state= MY_LEX_USER_VARIABLE_DELIMITER;
	break;
      }


    case MY_LEX_STRING:
    {
      uint sep;
      if (lip->get_text(&yylval->lex_str, (sep= lip->yyGetLast()), 1, 1))
      {
	state= MY_LEX_CHAR;
	break;
      }
      CHARSET_INFO *strcs= lip->m_underscore_cs ? lip->m_underscore_cs : cs;
      lip->body_utf8_append(lip->m_cpp_text_start);

      lip->body_utf8_append_escape(thd, &yylval->lex_str, strcs,
                                   lip->m_cpp_text_end, sep);
      lip->m_underscore_cs= NULL;

      lex->text_string_is_7bit= (lip->tok_bitmap & 0x80) ? 0 : 1;
      return(TEXT_STRING);
    }
    case MY_LEX_COMMENT:
      lex->select_lex.options|= OPTION_FOUND_COMMENT;
      while ((c = lip->yyGet()) != '\n' && c) ;
      lip->yyUnget();
      state = MY_LEX_START;
      break;
    case MY_LEX_LONG_COMMENT:
      if (lip->yyPeek() != '*')
      {
	state=MY_LEX_CHAR;
	break;
      }
      lex->select_lex.options|= OPTION_FOUND_COMMENT;

      lip->yyUnget();

      lip->save_in_comment_state();

      if (lip->yyPeekn(2) == '!' ||
          (lip->yyPeekn(2) == 'M' && lip->yyPeekn(3) == '!'))
      {
        bool maria_comment_syntax= lip->yyPeekn(2) == 'M';
        lip->in_comment= DISCARD_COMMENT;

        lip->set_echo(FALSE);
        lip->yySkipn(maria_comment_syntax ? 4 : 3);


        if (  my_isdigit(cs, lip->yyPeekn(0))
           && my_isdigit(cs, lip->yyPeekn(1))
           && my_isdigit(cs, lip->yyPeekn(2))
           && my_isdigit(cs, lip->yyPeekn(3))
           && my_isdigit(cs, lip->yyPeekn(4))
           )
        {
          ulong version;
          uint length= 5;
          char *end_ptr= (char*) lip->get_ptr()+length;
          int error;
          if (my_isdigit(cs, lip->yyPeekn(5)))
          {
            end_ptr++;
            length++;
          }

          version= (ulong) my_strtoll10(lip->get_ptr(), &end_ptr, &error);


          if (version <= MYSQL_VERSION_ID &&
              (version < 50700 || version > 99999 || maria_comment_syntax))
          {

            lip->yySkipn(length);

            lip->set_echo(TRUE);
            state=MY_LEX_START;
            break;
          }
          else
          {
#ifdef WITH_WSREP
	    if (WSREP(thd) && version == 99997 && thd->wsrep_exec_mode == LOCAL_STATE)
	    {
	      WSREP_DEBUG("consistency check: %s", thd->query());
	      thd->wsrep_consistency_check= CONSISTENCY_CHECK_DECLARED;
	      lip->yySkipn(5);
	      lip->set_echo(TRUE);
	      state=MY_LEX_START;
	      break;
	    }
#endif


            char *pcom= lip->yyUnput(' ');
            comment_closed= ! consume_comment(lip, 1);
            if (! comment_closed)
            {
              *pcom= '!';
            }

          }
        }
        else
        {

          state=MY_LEX_START;
          lip->set_echo(TRUE);
          break;
        }
      }
      else
      {
        lip->in_comment= PRESERVE_COMMENT;
        lip->yySkip();
        lip->yySkip();
        comment_closed= ! consume_comment(lip, 0);

      }


      if (! comment_closed)
        return (ABORT_SYM);
      state = MY_LEX_START;
      lip->restore_in_comment_state();
      break;
    case MY_LEX_END_LONG_COMMENT:
      if ((lip->in_comment != NO_COMMENT) && lip->yyPeek() == '/')
      {

        lip->yyUnget();

        lip->set_echo(lip->in_comment == PRESERVE_COMMENT);
        lip->yySkipn(2);

        lip->set_echo(TRUE);
        lip->in_comment=NO_COMMENT;
        state=MY_LEX_START;
      }
      else
	state=MY_LEX_CHAR;
      break;
    case MY_LEX_SET_VAR:
      if (lip->yyPeek() != '=')
      {
	state=MY_LEX_CHAR;
	break;
      }
      lip->yySkip();
      return (SET_VAR);
    case MY_LEX_SEMICOLON:
      state= MY_LEX_CHAR;
      break;
    case MY_LEX_EOL:
      if (lip->eof())
      {
        lip->yyUnget();
        lip->set_echo(FALSE);
        lip->yySkip();
        lip->set_echo(TRUE);

        if (lip->in_comment != NO_COMMENT)
          return (ABORT_SYM);
        lip->next_state=MY_LEX_END;
        return(END_OF_INPUT);
      }
      state=MY_LEX_CHAR;
      break;
    case MY_LEX_END:
      lip->next_state=MY_LEX_END;
      return(0);


    case MY_LEX_REAL_OR_POINT:
      if (my_isdigit(cs,lip->yyPeek()))
	state = MY_LEX_REAL;
      else
      {
	state= MY_LEX_IDENT_SEP;
        lip->yyUnget();
      }
      break;
    case MY_LEX_USER_END:
      switch (state_map[(uchar) lip->yyPeek()]) {
      case MY_LEX_STRING:
      case MY_LEX_USER_VARIABLE_DELIMITER:
      case MY_LEX_STRING_OR_DELIMITER:
	break;
      case MY_LEX_USER_END:
	lip->next_state=MY_LEX_SYSTEM_VAR;
	break;
      default:
	lip->next_state=MY_LEX_HOSTNAME;
	break;
      }
      yylval->lex_str.str=(char*) lip->get_ptr();
      yylval->lex_str.length=1;
      return((int) '@');
    case MY_LEX_HOSTNAME:
      for (c=lip->yyGet() ;
	   my_isalnum(cs,c) || c == '.' || c == '_' ||  c == '$';
           c= lip->yyGet()) ;
      yylval->lex_str=get_token(lip, 0, lip->yyLength());
      return(LEX_HOSTNAME);
    case MY_LEX_SYSTEM_VAR:
      yylval->lex_str.str=(char*) lip->get_ptr();
      yylval->lex_str.length=1;
      lip->yySkip();
      lip->next_state= (state_map[(uchar) lip->yyPeek()] ==
			MY_LEX_USER_VARIABLE_DELIMITER ?
			MY_LEX_OPERATOR_OR_IDENT :
			MY_LEX_IDENT_OR_KEYWORD);
      return((int) '@');
    case MY_LEX_IDENT_OR_KEYWORD:


      for (result_state= 0; ident_map[c= lip->yyGet()]; result_state|= c)
        ;

      result_state= result_state & 0x80 ? IDENT_QUOTED : IDENT;

      if (c == '.')
	lip->next_state=MY_LEX_IDENT_SEP;
      length= lip->yyLength();
      if (length == 0)
        return(ABORT_SYM);
      if ((tokval= find_keyword(lip, length,0)))
      {
        lip->yyUnget();
	return(tokval);
      }
      yylval->lex_str=get_token(lip, 0, length);

      lip->body_utf8_append(lip->m_cpp_text_start);

      lip->body_utf8_append_ident(thd, &yylval->lex_str, lip->m_cpp_text_end);

      return(result_state);
    }
  }
}
