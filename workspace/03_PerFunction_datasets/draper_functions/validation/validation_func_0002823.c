check_input_sections
  (lang_statement_union_type *s,
   lang_output_section_statement_type *output_section_statement)
{
  for (; s != (lang_statement_union_type *) NULL; s = s->header.next)
    {
      switch (s->header.type)
	{
	case lang_wild_statement_enum:
	  walk_wild (&s->wild_statement, check_section_callback,
		     output_section_statement);
	  if (! output_section_statement->all_input_readonly)
	    return;
	  break;
	case lang_constructors_statement_enum:
	  check_input_sections (constructor_list.head,
				output_section_statement);
	  if (! output_section_statement->all_input_readonly)
	    return;
	  break;
	case lang_group_statement_enum:
	  check_input_sections (s->group_statement.children.head,
				output_section_statement);
	  if (! output_section_statement->all_input_readonly)
	    return;
	  break;
	default:
	  break;
	}
    }
}
