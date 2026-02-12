MatchClass(class, input)
    register char class;
    register char input;
{
    register char c;
    register int retval;
    retval = 0;

    switch (class)
    {


    case '?':
	if (input == '?')
	{
	    retval = 1;
	}
	break;


    case 'V':
    case 'v':
	c = CRACK_TOLOWER(input);
	if (strchr("aeiou", c))
	{
	    retval = 1;
	}
	break;

    case 'C':
    case 'c':
	c = CRACK_TOLOWER(input);
	if (strchr("bcdfghjklmnpqrstvwxyz", c))
	{
	    retval = 1;
	}
	break;

    case 'W':
    case 'w':
	if (strchr("\t ", input))
	{
	    retval = 1;
	}
	break;

    case 'P':
    case 'p':
	if (strchr(".`,:;'!?\"", input))
	{
	    retval = 1;
	}
	break;

    case 'S':
    case 's':
	if (strchr("$%%^&*()-_+=|\\[]{}#@/~", input))
	{
	    retval = 1;
	}
	break;


    case 'L':
    case 'l':
	if (islower(input))
	{
	    retval = 1;
	}
	break;

    case 'U':
    case 'u':
	if (isupper(input))
	{
	    retval = 1;
	}
	break;

    case 'A':
    case 'a':
	if (isalpha(input))
	{
	    retval = 1;
	}
	break;

    case 'X':
    case 'x':
	if (isalnum(input))
	{
	    retval = 1;
	}
	break;

    case 'D':
    case 'd':
	if (isdigit(input))
	{
	    retval = 1;
	}
	break;

    default:
	Debug(1, "MatchClass: unknown class %c\n", class);
	return (0);
	break;
    }

    if (isupper(class))
    {
	return (!retval);
    }
    return (retval);
}
