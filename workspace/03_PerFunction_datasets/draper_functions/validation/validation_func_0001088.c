_skip_block (struct line_expander *exp)
{
  int level = exp->level;
  if (*exp->cp != '{')
    return;
  for (; *exp->cp; exp->cp++)
    {
      switch (*exp->cp)
	{
	case '{':
	  exp->level++;
	  break;

	case '}':
	  exp->level--;
	  if (exp->level == level)
	    {
	      exp->cp++;
	      return;
	    }
	}
    }
}
