copy_insn_regexp (regexp_t regexp)
{
  regexp_t  result;
  int i;

  if (regexp->mode == rm_reserv)
    result = copy_insn_regexp (REGEXP_RESERV (regexp)->reserv_decl->regexp);
  else if (regexp->mode == rm_unit)
    result = copy_node (regexp, sizeof (struct regexp));
  else if (regexp->mode == rm_repeat)
    {
      result = copy_node (regexp, sizeof (struct regexp));
      REGEXP_REPEAT (result)->regexp
        = copy_insn_regexp (REGEXP_REPEAT (regexp)->regexp);
    }
  else if (regexp->mode == rm_sequence)
    {
      result = copy_node (regexp,
                          sizeof (struct regexp) + sizeof (regexp_t)
			  * (REGEXP_SEQUENCE (regexp)->regexps_num - 1));
      for (i = 0; i <REGEXP_SEQUENCE (regexp)->regexps_num; i++)
	REGEXP_SEQUENCE (result)->regexps [i]
	  = copy_insn_regexp (REGEXP_SEQUENCE (regexp)->regexps [i]);
    }
  else if (regexp->mode == rm_allof)
    {
      result = copy_node (regexp,
                          sizeof (struct regexp) + sizeof (regexp_t)
			  * (REGEXP_ALLOF (regexp)->regexps_num - 1));
      for (i = 0; i < REGEXP_ALLOF (regexp)->regexps_num; i++)
	REGEXP_ALLOF (result)->regexps [i]
	  = copy_insn_regexp (REGEXP_ALLOF (regexp)->regexps [i]);
    }
  else if (regexp->mode == rm_oneof)
    {
      result = copy_node (regexp,
                          sizeof (struct regexp) + sizeof (regexp_t)
			  * (REGEXP_ONEOF (regexp)->regexps_num - 1));
      for (i = 0; i < REGEXP_ONEOF (regexp)->regexps_num; i++)
	REGEXP_ONEOF (result)->regexps [i]
	  = copy_insn_regexp (REGEXP_ONEOF (regexp)->regexps [i]);
    }
  else
    {
      if (regexp->mode != rm_nothing)
	abort ();
      result = copy_node (regexp, sizeof (struct regexp));
    }
  return result;
}
