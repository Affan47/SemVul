accept (char c, enum special sym)
{
	switch (sym)
	{
		case DOT :
			return 1;
		case EPSILON :
			return ( c == special_symbols [EPSILON]) ? 1 : 0;
		case CAPITAL_LETTERS :
			return ( c >= 'A' && c <= 'Z' ) ? 1 : 0;
		case SMALL_LETTERS :
			return ( c >= 'a' && c <= 'z' ) ? 1 : 0;
		case DIGITS :
			return ( c >= '0' && c <= '9' ) ? 1 : 0;
		default :
			return 0;
	}
}
