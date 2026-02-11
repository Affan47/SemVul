set_header(char *arg)
{
	switch  (tolower(*arg))  {
	case  'y':case '1':
		headerflag = 1;
		return  1;
	case  'n':case '0':
		headerflag = 0;
		return  1;
	default:
		return  0;
	}
}
