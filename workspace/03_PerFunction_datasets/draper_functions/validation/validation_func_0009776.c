do_line (cpp_reader *pfile)
{
  const cpp_token *token;
  const char *new_file = pfile->map->to_file;
  unsigned long new_lineno;


  unsigned int cap = CPP_OPTION (pfile, c99) ? 2147483647 : 32767;


  token = cpp_get_token (pfile);
  if (token->type != CPP_NUMBER
      || strtoul_for_line (token->val.str.text, token->val.str.len,
			   &new_lineno))
    {
      cpp_error (pfile, CPP_DL_ERROR,
		 "\"%s\" after #line is not a positive integer",
		 cpp_token_as_text (pfile, token));
      return;
    }

  if (CPP_PEDANTIC (pfile) && (new_lineno == 0 || new_lineno > cap))
    cpp_error (pfile, CPP_DL_PEDWARN, "line number out of range");

  token = cpp_get_token (pfile);
  if (token->type == CPP_STRING)
    {
      cpp_string s = { 0, 0 };
      if (_cpp_interpret_string_notranslate (pfile, &token->val.str, &s))
	new_file = (const char *)s.text;
      check_eol (pfile);
    }
  else if (token->type != CPP_EOF)
    {
      cpp_error (pfile, CPP_DL_ERROR, "\"%s\" is not a valid filename",
		 cpp_token_as_text (pfile, token));
      return;
    }

  skip_rest_of_line (pfile);
  _cpp_do_file_change (pfile, LC_RENAME, new_file, new_lineno,
		       pfile->map->sysp);
}
