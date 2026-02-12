sh_contains_shell_metas (string)
     char *string;
{
  char *s;

  for (s = string; s && *s; s++)
    {
      switch (*s)
	{
	case ' ': case '\t': case '\n':
	case '\'': case '"': case '\\':
	case '|': case '&': case ';':
	case '(': case ')': case '<': case '>':
	case '!': case '{': case '}':
	case '*': case '[': case '?': case ']':
	case '^':
	case '$': case '`':
	  return (1);
	case '~':
	  if (s == string || s[-1] == '=' || s[-1] == ':')
	    return (1);
	  break;
	case '#':
	  if (s == string)
	    return (1);

	default:
	  break;
	}
    }

  return (0);
}
