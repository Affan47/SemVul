write_unqualified_id (tree identifier)
{
  if (IDENTIFIER_TYPENAME_P (identifier))
    write_conversion_operator_name (TREE_TYPE (identifier));
  else if (IDENTIFIER_OPNAME_P (identifier))
    {
      int i;
      const char *mangled_name = NULL;


      for (i = 0; i < MAX_TREE_CODES; ++i)
	if (operator_name_info[i].identifier == identifier)
	  {


	    if (operator_name_info[i].arity == 2)
	      {
		mangled_name = operator_name_info[i].mangled_name;
		break;
	      }
	    else if (!mangled_name)
	      mangled_name = operator_name_info[i].mangled_name;
	  }
	else if (assignment_operator_name_info[i].identifier
		 == identifier)
	  {
	    mangled_name
	      = assignment_operator_name_info[i].mangled_name;
	    break;
	  }
      write_string (mangled_name);
    }
  else if (UDLIT_OPER_P (identifier))
    write_literal_operator_name (identifier);
  else
    write_source_name (identifier);
}
