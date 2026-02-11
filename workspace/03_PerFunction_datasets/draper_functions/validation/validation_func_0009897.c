parse_declarator_id (const char *&str, MatchName &match_name) {
  skip_blanks (str);

  const char *curr = str;
  if (!parse_nested_name (curr, match_name))
    if (error ())
      return false;
  skip_blanks (curr);

  const char *name_start = curr;
  while (is_id (*curr))
    curr++;
  if (curr == name_start)
    return false;
  int len = curr - name_start;

  if (len == 8 && strncmp (name_start, "operator", 8) == 0) {

    skip_blanks (curr);
    MatchName::Operator oper;

    if (parse_operator_id (curr, oper)) {
      match_name.oper (oper);
    }
    else {

      MatchTypeRef conv_type;
      if (parse_conv_id (curr, conv_type))
        match_name.conv_type (conv_type);
      else {
        _state = ERR_INVALID_OPER;
        return false;
      }
    }
  }
  else {

    string name (name_start, curr - name_start);
    match_name.name (DString (name.c_str ()));
  }
  str = curr;


  MatchTemplateArgList *mtal;
  if (!parse_opt_template_argument_list (str, mtal))
    if (error ())
      return false;

  match_name.template_args (mtal);
  return true;
}
