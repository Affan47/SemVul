reload_frozen_state (const char *name)
{
  FILE *file;
  int character;
  int operation;
  char *string[2];
  int allocated[2];
  int number[2];
  const builtin *bp;

#define GET_CHARACTER \
  (character = getc (file))

#define GET_NUMBER(Number) \
  do								\
    {								\
      (Number) = 0;						\
      while (isdigit (character))				\
	{							\
	  (Number) = 10 * (Number) + character - '0';		\
	  GET_CHARACTER;					\
	}							\
    }								\
  while (0)

#define VALIDATE(Expected) \
  do								\
    {								\
      if (character != (Expected))				\
	issue_expect_message ((Expected));			\
    }								\
  while (0)


#define GET_DIRECTIVE \
  do								\
    {								\
      GET_CHARACTER;						\
      if (character == '#')					\
	{							\
	  while (character != EOF && character != '\n')		\
	    GET_CHARACTER;					\
	  VALIDATE ('\n');					\
	}							\
    }								\
  while (character == '\n')

  file = m4_path_search (name, NULL);
  if (file == NULL)
    M4ERROR ((EXIT_FAILURE, errno, "cannot open %s", name));

  allocated[0] = 100;
  string[0] = xcharalloc ((size_t) allocated[0]);
  allocated[1] = 100;
  string[1] = xcharalloc ((size_t) allocated[1]);


  GET_DIRECTIVE;
  VALIDATE ('V');
  GET_CHARACTER;
  GET_NUMBER (number[0]);
  if (number[0] > 1)
    M4ERROR ((EXIT_MISMATCH, 0,
	      "frozen file version %d greater than max supported of 1",
	      number[0]));
  else if (number[0] < 1)
    M4ERROR ((EXIT_FAILURE, 0,
	      "ill-formed frozen file, version directive expected"));
  VALIDATE ('\n');

  GET_DIRECTIVE;
  while (character != EOF)
    {
      switch (character)
	{
	default:
	  M4ERROR ((EXIT_FAILURE, 0, "ill-formed frozen file"));

	case 'C':
	case 'D':
	case 'F':
	case 'T':
	case 'Q':
	  operation = character;
	  GET_CHARACTER;


	  if (operation == 'D' && character == '-')
	    {
	      GET_CHARACTER;
	      GET_NUMBER (number[0]);
	      number[0] = -number[0];
	    }
	  else
	    GET_NUMBER (number[0]);
	  VALIDATE (',');
	  GET_CHARACTER;
	  GET_NUMBER (number[1]);
	  VALIDATE ('\n');

	  if (operation != 'D')
	    {


	      if (number[0] + 1 > allocated[0])
		{
		  free (string[0]);
		  allocated[0] = number[0] + 1;
		  string[0] = xcharalloc ((size_t) allocated[0]);
		}

	      if (number[0] > 0)
		if (!fread (string[0], (size_t) number[0], 1, file))
		  M4ERROR ((EXIT_FAILURE, 0, "premature end of frozen file"));

	      string[0][number[0]] = '\0';
	    }


	  if (number[1] + 1 > allocated[1])
	    {
	      free (string[1]);
	      allocated[1] = number[1] + 1;
	      string[1] = xcharalloc ((size_t) allocated[1]);
	    }

	  if (number[1] > 0)
	    if (!fread (string[1], (size_t) number[1], 1, file))
	      M4ERROR ((EXIT_FAILURE, 0, "premature end of frozen file"));

	  string[1][number[1]] = '\0';
	  GET_CHARACTER;
	  VALIDATE ('\n');


	  switch (operation)
	    {
	    case 'C':


	      set_comment (string[0], string[1]);
	      break;

	    case 'D':


	      make_diversion (number[0]);
	      if (number[1] > 0)
		output_text (string[1], number[1]);
	      break;

	    case 'F':


	      bp = find_builtin_by_name (string[1]);
	      define_builtin (string[0], bp, SYMBOL_PUSHDEF);
	      break;

	    case 'T':


	      define_user_macro (string[0], string[1], SYMBOL_PUSHDEF);
	      break;

	    case 'Q':


	      set_quotes (string[0], string[1]);
	      break;

	    default:


	      break;
	    }
	  break;

	}
      GET_DIRECTIVE;
    }

  free (string[0]);
  free (string[1]);
  errno = 0;
  if (ferror (file) || fclose (file) != 0)
    M4ERROR ((EXIT_FAILURE, errno, "unable to read frozen state"));

#undef GET_CHARACTER
#undef GET_DIRECTIVE
#undef GET_NUMBER
#undef VALIDATE
}
