getsym()
{
    register char *reglineptr;

    reglineptr = lineptr;
advance:
    symname = reglineptr;
    switch (sym = symofchar[(unsigned char) *reglineptr++])
    {
    case WHITESPACE:
	goto advance;
    case ADDOP:
	if (*reglineptr == '+')
	{
	    sym = POSTINCOP;
	    ++reglineptr;
	}
	break;
    case BINCONST:
	numbase = 2;
	lineptr = reglineptr;
	intconst();
	return;
    case CHARCONST:
	if ((number = *reglineptr) < ' ')
	    number = ' ';
	if (*reglineptr != EOL)
	    ++reglineptr;
	sym = INTCONST;
	break;
    case GREATERTHAN:
	if (*reglineptr == '>')
	{
	    sym = SROP;
	    ++reglineptr;
	}
	break;
    case HEXCONST:
	numbase = 16;
	lineptr = reglineptr;
	intconst();
	return;
    case IDENT:

	while (symofchar[(unsigned char) *reglineptr] <= INTCONST)
	    ++reglineptr;
	lineptr = reglineptr;
	gsymptr = lookup();
	return;
    case INTCONST:
	if (*(reglineptr - 1) == '0')
	{
	    if (*reglineptr != 'x' && *reglineptr != 'X')
		numbase = 8;
	    else
	    {
		numbase = 16;
		++reglineptr;
	    }
	}
	else
	{
	    --reglineptr;
	    numbase = 10;
	}
	lineptr = reglineptr;
	intconst();
	return;
    case LESSTHAN:
	if (*reglineptr == '<')
	{
	    sym = SLOP;
	    ++reglineptr;
	}
	break;
    case SUBOP:
	if (*reglineptr == '-')
	{
	    sym = PREDECOP;
	    ++reglineptr;
	}
	break;
    }
    lineptr = reglineptr;
    return;
}
