GetWordNum(int num, char * l_String)
{
	static char strreturn[600];
	static char ptokstr[600];
	char seps[10] = NOX(" \n\r\t");
	char *token,*strstart;

	strreturn[sizeof(strreturn)-1] = '\0';
	ptokstr[sizeof(ptokstr)-1] = '\0';

	strstart = ptokstr;

	strncpy(ptokstr, l_String, sizeof(ptokstr)-1);

	token=strtok(ptokstr,seps);

	for(int i=0;i!=num;i++)
	{
		token=strtok(NULL,seps);
	}
	if(token)
	{
		strncpy(strreturn, token, sizeof(strreturn)-1);
	}
	else
	{
		return "";
	}

	if(token[0]==':')
	{

		strncpy(strreturn, l_String+((token-strstart)+1), sizeof(strreturn)-1);
	}


	return strreturn;
}
