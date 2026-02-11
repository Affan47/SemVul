read_skip_spaces (void)
{
  int c;

  while (1)
    {
      c = read_char ();
      switch (c)
	{
	case ' ': case '\t': case '\f': case '\r': case '\n':
	  break;

	case ';':
	  do
	    c = read_char ();
	  while (c != '\n' && c != EOF);
	  break;

	case '/':
	  {
	    int prevc;
	    c = read_char ();
	    if (c != '*')
	      {
		unread_char (c);
		fatal_with_file_and_line ("stray '/' in file");
	      }

	    prevc = 0;
	    while ((c = read_char ()) && c != EOF)
	      {
		if (prevc == '*' && c == '/')
		  break;
	        prevc = c;
	      }
	  }
	  break;

	default:
	  return c;
	}
    }
}
