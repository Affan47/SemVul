mylex (krb5_int32 *intp, char **pp)
{
    int num, c;
#define P (*pp)
    char *orig_p = P;

#ifdef isascii
    if (!isascii (*P))
	return 0;
#endif
    switch (c = *P++) {
    case '-':
    case ':':
    case 'd':
    case 'h':
    case 'm':
    case 's':
	return c;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':

	num = c - '0';
	while (isdigit ((int) *P)) {
	  if (num > MAX_TIME / 10)
	    return OVERFLOW;
	    num *= 10;
	    if (num > MAX_TIME - (*P - '0'))
	      return OVERFLOW;
	    num += *P++ - '0';
	}
	*intp = num;
	return (P - orig_p > 2) ? LONGNUM : NUM;
    case ' ':
    case '\t':
    case '\n':
	while (isspace ((int) *P))
	    P++;
	return tok_WS;
    default:
	return YYEOF;
    }
}
